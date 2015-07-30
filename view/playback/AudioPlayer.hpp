//
// Created by toramisu on 2015/7/30.
//

#pragma once

#include "string"

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

class AudioPlayer {
public:
    AVFormatContext *formatContext = nullptr;
    AVCodecContext *codecContext = nullptr;
    PaStream *stream = nullptr;
    AVPacket packet;
    AudioContext context;
    AVFrame *frame = nullptr;

    AudioPlayer() {

//        Evt_add(PlaybackEvent::FORWARD, onForward)
    }
    void onForward(void*e) {
//        seek(20000);
    }

    void play() {
        std::thread t([this] { _run(); });
        t.detach();
    }

    void load(std::string filename) {

        // 将要打开的音频文件(视频文件也可以支持).
//        const char *filename =string.;

        // 初始化libavformat,并注册所有的模块
        av_register_all();

        // 这里一定要设置成NULL, 或者调用avformat_alloc_context分配内存, 否则可能崩溃.
        formatContext = NULL;
        // 打开输入文件.
        if (avformat_open_input(&formatContext, filename.c_str(), NULL, NULL) < 0) {
            std::cerr << "cannot open file" << std::endl;
            return;
        }

        // 探测文件里面的音视频流信息.
        if (avformat_find_stream_info(formatContext, NULL) < 0) {
            std::cerr << "cannot find stream info" << std::endl;
            return;
        }

        // 输出来看看.
        av_dump_format(formatContext, 0, 0, 0);

        // 找到音频流的索引(如果是视频的话,可能存在多个流).
        int audioIndex;
        if ((audioIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, 0, 0, NULL, 0)) < 0) {
            std::cerr << "cannot find audio stream" << std::endl;
            return;
        }

        codecContext = formatContext->streams[audioIndex]->codec;
        // 找到解码器.
        AVCodec *codec = avcodec_find_decoder(codecContext->codec_id);
        if (codec == NULL) {
            std::cerr << "cannot find decoder for " << codecContext->codec_name << std::endl;
        }

        // 打开解码器.
        if (avcodec_open2(codecContext, codec, NULL) < 0) {
            std::cerr << "cannot open decoder" << std::endl;
            return;
        }

        // AVPacket是解码前的数据, AVFrame是解码后的数据.
        frame = av_frame_alloc();
        context.resamplerContext = NULL;
        context.swrContext = NULL;
        context.codecContext = codecContext;

        // 下面是初始化PortAudio, 用PortAudio的Blocking API比较简单.

//        Pa_Initialize();
//        PaStreamParameters outputParameters;
//        outputParameters.device = Pa_GetDefaultOutputDevice();
//        if (outputParameters.device != paNoDevice) {
//            outputParameters.channelCount = codecContext->channels;
//            outputParameters.sampleFormat = codecContext->sample_fmt;
//            outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
//            outputParameters.hostApiSpecificStreamInfo = NULL;
//            PaError ret = Pa_OpenStream(&stream,
//                                        NULL,
//                                        &outputParameters,
//                                        codecContext->sample_rate,
//                                        paFramesPerBufferUnspecified, // framesPerBuffer
//                                        0, // flags
//                                        paStreamCallback,
//                                        this);
//
//
//            if (ret != paNoError) {
//                fprintf(stderr, "Pa_OpenStream failed: (err %i) %s\n", ret, Pa_GetErrorText(ret));
//                if (stream)
//                    Pa_CloseStream(stream);
//                return;
//            }
//            Pa_StartStream(stream);
//        }
//////////////////////////////
        Pa_Initialize();
        Pa_OpenDefaultStream(&stream, 0, codecContext->channels,
                             paInt16, codecContext->sample_rate,
                             1024, NULL, NULL);
        Pa_StartStream(stream);

//        while (true) {
//            // 从文件中读取一帧.
//            if (av_read_frame(formatContext, &packet) < 0) {
//                // 文件读完了.
//                break;
//            }
//
//            // 解码.
//            if (avcodec_decode_audio4(codecContext, frame, &got, &packet) < 0) {
//                std::cerr << "cannot decode" << std::endl;
//                // 偶尔会出错,一般都可以原谅的...
//                // break;
//            }
//            // 解码出来了一帧
//            if (got) {
//                // 因为frame->data[0]表示的是左声道LLL....,frame->data[1]表示右声道RRR...
//                // 而PortAudio要求的是LRLRLR....这样的数据排布, 所以这里用循环重新将数据复制到buffer中
//                AVFrame *dst = av_frame_alloc();
//                audio_copy(&context, dst, frame);
//                Pa_WriteStream(stream, reinterpret_cast<int16_t *>(dst->data[0]), dst->nb_samples);
//            }
//        }
    }

    void seek(int posInms) {
        if (formatContext) {
            av_seek_frame(formatContext, -1, posInms / 1000 * AV_TIME_BASE, AVSEEK_FLAG_ANY);
            avcodec_flush_buffers(codecContext);
        }
    }

private:
    void _run() {
        int got;
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
    }
};