//
// Created by toramisu on 2015/7/30.
//
// 这里是ffmpeg的头文件, 如果是用c++, 必须加上extern "C", 否则可能导致链接时出错.
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}

// 这里是PortAudio的头文件
#include <portaudio.h>
#include <assert.h>
#include <iostream>

struct AudioContext {
    AVCodecContext *codecContext;
    SwrContext *swrContext;
    ReSampleContext *resamplerContext;
};


static void audio_copy(AudioContext *context, AVFrame *dst, AVFrame *src) {
    int nb_sample;
    int dst_buf_size;
    int out_channels;
    int bytes_per_sample = 0;

    dst->linesize[0] = src->linesize[0];
    *dst = *src;
    dst->data[0] = NULL;
    dst->type = 0;

    /* 备注: FFMIN(codecContext->channels, 2); 会有问题, 因为swr_alloc_set_opts的out_channel_layout参数. */
    out_channels = context->codecContext->channels;

    bytes_per_sample = av_get_bytes_per_sample(context->codecContext->sample_fmt);
    /* 备注: 由于 src->linesize[0] 可能是错误的, 所以计算得到的nb_sample会不正确, 直接使用src->nb_samples即可. */
    nb_sample = src->nb_samples;/* src->linesize[0] / codecContext->channels / bytes_per_sample; */
    bytes_per_sample = av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
    dst_buf_size = nb_sample * bytes_per_sample * out_channels;
    dst->data[0] = (uint8_t *) av_malloc(dst_buf_size);
    assert(dst->data[0]);
    avcodec_fill_audio_frame(dst, out_channels, AV_SAMPLE_FMT_S16, dst->data[0], dst_buf_size, 0);

    /* 重采样到AV_SAMPLE_FMT_S16格式. */
    if (context->codecContext->sample_fmt != AV_SAMPLE_FMT_S16) {
        if (!context->swrContext) {
            uint64_t in_channel_layout = av_get_default_channel_layout(context->codecContext->channels);
            uint64_t out_channel_layout = av_get_default_channel_layout(out_channels);
            context->swrContext = swr_alloc_set_opts(NULL,
                                                     out_channel_layout, AV_SAMPLE_FMT_S16,
                                                     context->codecContext->sample_rate,
                                                     in_channel_layout, context->codecContext->sample_fmt,
                                                     context->codecContext->sample_rate,
                                                     0, NULL);
            swr_init(context->swrContext);
        }

        if (context->swrContext) {
            int ret, out_count;
            out_count = dst_buf_size / out_channels / av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
            ret = swr_convert(context->swrContext, dst->data, out_count, const_cast<const uint8_t **>(src->data),
                              nb_sample);
            if (ret < 0)
                assert(0);
            src->linesize[0] = dst->linesize[0] = ret * av_get_bytes_per_sample(AV_SAMPLE_FMT_S16) * out_channels;
            memcpy(src->data[0], dst->data[0], src->linesize[0]);
        }
    }

    /* 重采样到双声道. */
    if (context->codecContext->channels > 2) {
        if (!context->resamplerContext) {
            context->resamplerContext = av_audio_resample_init(
                    FFMIN(2, context->codecContext->channels),
                    context->codecContext->channels, context->codecContext->sample_rate,
                    context->codecContext->sample_rate, AV_SAMPLE_FMT_S16, AV_SAMPLE_FMT_S16,
                    16, 10, 0, 0.f);
        }

        if (context->resamplerContext) {
            int samples =
                    src->linesize[0] / (av_get_bytes_per_sample(AV_SAMPLE_FMT_S16) * context->codecContext->channels);
            dst->linesize[0] = audio_resample(context->resamplerContext,
                                              (short *) dst->data[0], (short *) src->data[0], samples) * 4;
        }
    }
    else {
        dst->linesize[0] = dst->linesize[0];
        memcpy(dst->data[0], src->data[0], dst->linesize[0]);
    }
}


int ffmain() {

    // 将要打开的音频文件(视频文件也可以支持).
    const char *filename = "test\\test.wav";

    // 初始化libavformat,并注册所有的模块
    av_register_all();

    // 这里一定要设置成NULL, 或者调用avformat_alloc_context分配内存, 否则可能崩溃.
    AVFormatContext *formatContext = NULL;

    // 打开输入文件.
    if (avformat_open_input(&formatContext, filename, NULL, NULL) < 0) {
        std::cerr << "cannot open file" << std::endl;
        return -1;
    }

    // 探测文件里面的音视频流信息.
    if (avformat_find_stream_info(formatContext, NULL) < 0) {
        std::cerr << "cannot find stream info" << std::endl;
        return -1;
    }

    // 输出来看看.
    av_dump_format(formatContext, 0, 0, 0);

    // 找到音频流的索引(如果是视频的话,可能存在多个流).
    int audioIndex;
    if ((audioIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, 0, 0, NULL, 0)) < 0) {
        std::cerr << "cannot find audio stream" << std::endl;
        return -1;
    }

    AVCodecContext *codecContext = formatContext->streams[audioIndex]->codec;
    // 找到解码器.
    AVCodec *codec = avcodec_find_decoder(codecContext->codec_id);
    if (codec == NULL) {
        std::cerr << "cannot find decoder for " << codecContext->codec_name << std::endl;
    }

    // 打开解码器.
    if (avcodec_open2(codecContext, codec, NULL) < 0) {
        std::cerr << "cannot open decoder" << std::endl;
        return -1;
    }

    // AVPacket是解码前的数据, AVFrame是解码后的数据.
    AVPacket packet;
    AVFrame *frame = av_frame_alloc();
    int got;
    AudioContext context;
    context.resamplerContext = NULL;
    context.swrContext = NULL;
    context.codecContext = codecContext;

    // 下面是初始化PortAudio, 用PortAudio的Blocking API比较简单.
    PaStream *stream;
    Pa_Initialize();
    Pa_OpenDefaultStream(&stream, 0, codecContext->channels,
                         paInt16, codecContext->sample_rate,
                         1024, NULL, NULL);
    Pa_StartStream(stream);
    codecContext->sample_fmt;
    int size = 4092;
    uint8_t *buffer = new uint8_t[size * 2];
    int channels = codecContext->channels;

    av_seek_frame(formatContext, -1, 10 * AV_TIME_BASE, AVSEEK_FLAG_ANY);
    avcodec_flush_buffers(codecContext);

    while (true) {
        // 从文件中读取一帧.
        if (av_read_frame(formatContext, &packet) < 0) {
            // 文件读完了.
            break;
        }

        // 解码.
        if (avcodec_decode_audio4(codecContext, frame, &got, &packet) < 0) {
            std::cerr << "cannot decode" << std::endl;
            // 偶尔会出错,一般都可以原谅的...
            // break;
        }
        // 解码出来了一帧
        if (got) {
            // 因为frame->data[0]表示的是左声道LLL....,frame->data[1]表示右声道RRR...
            // 而PortAudio要求的是LRLRLR....这样的数据排布, 所以这里用循环重新将数据复制到buffer中
            AVFrame *dst = av_frame_alloc();
            audio_copy(&context, dst, frame);
            Pa_WriteStream(stream, reinterpret_cast<int16_t *>(dst->data[0]), dst->nb_samples);
        }
    }
    delete buffer;
    return 0;
}





#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"

/* #define SAMPLE_RATE  (17932) /* Test failure to open with this value. */
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (1024)
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)
/* #define DITHER_FLAG     (paDitherOff)  */
#define DITHER_FLAG     (0) /**/

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
 #define PA_SAMPLE_TYPE  paInt16
 typedef short SAMPLE;
 #define SAMPLE_SILENCE  (0)
 #define PRINTF_S_FORMAT "%d"
 #elif 0
 #define PA_SAMPLE_TYPE  paInt8
 typedef char SAMPLE;
 #define SAMPLE_SILENCE  (0)
 #define PRINTF_S_FORMAT "%d"
 #else
 #define PA_SAMPLE_TYPE  paUInt8
 typedef unsigned char SAMPLE;
 #define SAMPLE_SILENCE  (128)
 #define PRINTF_S_FORMAT "%d"
 #endif

#define FORMATID "fmt "
#define DATAID   "data"

typedef struct {
    char chunkID[4];
    long chunkSize;
    short wFormatTag;
    unsigned short wChannels;
    unsigned long dwSamplesPerSec;
    unsigned long dwAvgBytesPerSec;
    unsigned short wBlockAlign;
    unsigned short wBitsPerSample;
} FormatChunk;

typedef struct {
    char chunkID[4];
    long chunkSize;
} DataChunkHeader;


int checkHeader(FILE *fid) {
    char riff[4];
    char wave[4];
    fread(riff, 4, sizeof(char), fid);
    /* throwaway 4 bytes */
    fread(wave, 4, sizeof(char), fid);
    fread(wave, 4, sizeof(char), fid);

    if (!((strncmp(riff, "RIFF", 4) == 0) &&
          (strncmp(wave, "WAVE", 4) == 0))) {
        return -1;
    }

    return 0;
}


int getData(FILE *fid, char **data) {

    DataChunkHeader dch;

    while (strncmp(dch.chunkID, DATAID, 4) != 0) {
        fread(&dch, sizeof(DataChunkHeader), 1, fid);
        if (feof(fid) || ferror(fid))
            return -1;
    }

    printf("Size of data: %d\n", dch.chunkSize);

    *data = (char *) malloc(dch.chunkSize * sizeof(char));
    fread(*data, sizeof(char), dch.chunkSize, fid);
    if (feof(fid) || ferror(fid)) {
        free(data);
        return -1;
    }

    return dch.chunkSize;
}

int getFormatChunk(FILE *fid, FormatChunk *formatChunk) {
    while (strncmp(formatChunk->chunkID, FORMATID, 4) != 0) {
        fread(formatChunk, sizeof(FormatChunk), 1, fid);
        if (feof(fid) || ferror(fid))
            return -1;
    }
    return 0;
}


/*******************************************************************/
int main2(int argc, char *argv[]) {
    PaStreamParameters outputParameters;
    PaStream *stream;
    PaError err;
    /*int i;
    int totalFrames;
    int numSamples;
    int numBytes;
    */

    /* read wave file */
    char *filename;
    FILE *fid;

    if (argc < 2) {
        printf("Usage: %s filename.wav\n", argv[0]);
        return -1;
    }

    /* filename */
    filename = argv[1];
    printf("Filename: %s\n", filename);

    /* open file */
    fid = fopen(filename, "rb");
    if (fid == NULL) {
        printf("Could not open file %s\n", filename);
        return -1;
    }

    /* check header */
    if (checkHeader(fid) < 0) {
        printf("Not a wave file!\n");
        return -1;
    }

    FormatChunk formatChunk;
    int data_size;
    char *data;

    if (getFormatChunk(fid, &formatChunk) < 0) {
        printf("Couldn't read header\n");
        return -1;
    }

    printf("Chunk Size       : %d\n", formatChunk.chunkSize);
    printf("Compressed       : %d\n", formatChunk.wFormatTag != 1);
    printf("Channels         : %d\n", formatChunk.wChannels);
    printf("SamplesPerSecond : %d\n", formatChunk.dwSamplesPerSec);
    printf("dwAvgBytesPerSec : %d\n", formatChunk.dwAvgBytesPerSec);
    printf("wBlockAlign      : %d\n", formatChunk.wBlockAlign);
    printf("wBitsPerSample   : %d\n", formatChunk.wBitsPerSample);

    if ((data_size = getData(fid, &data)) < 0) {
        printf("Couldn't read data\n");
        return -1;
    }

    int total_frames = data_size / formatChunk.wBlockAlign;

    printf("Total Frames     : %d\n", total_frames);
    /* fclose(fid); */


    err = Pa_Initialize();
    if (err != paNoError) goto error;

    /* Playback recorded data.  -------------------------------------------- */

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */

    outputParameters.channelCount = formatChunk.wChannels;
    outputParameters.sampleFormat = paInt16;

    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;

    printf("YO YO\n");
    fflush(stdout);
    outputParameters.hostApiSpecificStreamInfo = NULL;

    printf("Begin playback.\n");
    fflush(stdout);
    err = Pa_OpenStream(
            &stream,
            NULL, /* no input */
            &outputParameters,
            formatChunk.dwSamplesPerSec,
            0, /*FRAMES_PER_BUFFER, */
            paClipOff,      /* we won't output out of range samples so don't bother clipping them */
            NULL, /* no callback, use blocking API */
            NULL); /* no callback, so no callback userData */
    if (err != paNoError) goto error;

    if (stream) {
        err = Pa_StartStream(stream);
        if (err != paNoError) goto error;
        printf("Waiting for playback to finish.\n");
        fflush(stdout);

        err = Pa_WriteStream(stream, data, total_frames);
        if (err != paNoError) goto error;

        err = Pa_CloseStream(stream);
        if (err != paNoError) goto error;
        printf("Done.\n");
        fflush(stdout);
    }
    free(data);

    Pa_Terminate();
    return 0;

    error:
    Pa_Terminate();
    fprintf(stderr, "An error occured while using the portaudio stream\n");
    fprintf(stderr, "Error number: %d\n", err);
    fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
    return -1;
}