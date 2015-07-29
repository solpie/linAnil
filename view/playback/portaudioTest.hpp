//// Simple demo to play wav-file with PortAudio.
//// Part of MusicPlayer, https://github.com/albertz/music-player
//// Copyright (c) 2013, Albert Zeyer, www.az2000.de
//// All rights reserved.
//// This code is under the 2-clause BSD license.
//
//// compile:
////   c++ portaudio-wavplay-demo.cpp -lportaudio
//
//#include <stdio.h>
//#include <string.h>
//#include <portaudio.h>
//#include <string>
//#include <stdint.h>
//#include <unistd.h>
//
//#define CHECK(x) { if(!(x)) { \
//fprintf(stderr, "%s:%i: failure at: %s\n", __FILE__, __LINE__, #x); \
//_exit(1); } }
//
//PaStream *stream;
//FILE *wavfile;
//int numChannels;
//int sampleRate;
//PaSampleFormat sampleFormat;
//int bytesPerSample, bitsPerSample;
//
//int paStreamCallback(
//        const void *input, void *output,
//        unsigned long frameCount,
//        const PaStreamCallbackTimeInfo *timeInfo,
//        PaStreamCallbackFlags statusFlags,
//        void *userData) {
//    size_t numRead = fread(output, bytesPerSample * numChannels, frameCount, wavfile);
//    output = (uint8_t *) output + numRead * numChannels * bytesPerSample;
//    frameCount -= numRead;
//
//    if (frameCount > 0) {
//        memset(output, 0, frameCount * numChannels * bytesPerSample);
//        return paComplete;
//    }
//
//    return paContinue;
//}
//
//bool portAudioOpen() {
//    CHECK(Pa_Initialize() == paNoError);
//
//    PaStreamParameters outputParameters;
//
//    outputParameters.device = Pa_GetDefaultOutputDevice();
//    CHECK(outputParameters.device != paNoDevice);
//
//    outputParameters.channelCount = numChannels;
//    outputParameters.sampleFormat = sampleFormat;
//    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
//    outputParameters.hostApiSpecificStreamInfo = NULL;
//
//    PaError ret = Pa_OpenStream(
//            &stream,
//            NULL, // no input
//            &outputParameters,
//            sampleRate,
//            paFramesPerBufferUnspecified, // framesPerBuffer
//            0, // flags
//            &paStreamCallback,
//            NULL //void *userData
//    );
//
//    if (ret != paNoError) {
//        fprintf(stderr, "Pa_OpenStream failed: (err %i) %s\n", ret, Pa_GetErrorText(ret));
//        if (stream)
//            Pa_CloseStream(stream);
//        return false;
//    }
//
//    CHECK(Pa_StartStream(stream) == paNoError);
//    return true;
//}
//
//std::string freadStr(FILE *f, size_t len) {
//    std::string s(len, '\0');
//    CHECK(fread(&s[0], 1, len, f) == len);
//    return s;
//}
//
//template<typename T>
//T freadNum(FILE *f) {
//    T value;
//    CHECK(fread(&value, sizeof(value), 1, f) == 1);
//    return value; // no endian-swap for now... WAV is LE anyway...
//}
//
//void readFmtChunk(uint32_t chunkLen) {
//    CHECK(chunkLen >= 16);
//    uint16_t fmttag = freadNum<uint16_t>(wavfile); // 1: PCM (int). 3: IEEE float
//    CHECK(fmttag == 1 || fmttag == 3);
//    numChannels = freadNum<uint16_t>(wavfile);
//    CHECK(numChannels > 0);
//    printf("%i channels\n", numChannels);
//    sampleRate = freadNum<uint32_t>(wavfile);
//    printf("%i Hz\n", sampleRate);
//    uint32_t byteRate = freadNum<uint32_t>(wavfile);
//    uint16_t blockAlign = freadNum<uint16_t>(wavfile);
//    bitsPerSample = freadNum<uint16_t>(wavfile);
//    bytesPerSample = bitsPerSample / 8;
//    CHECK(byteRate == sampleRate * numChannels * bytesPerSample);
//    CHECK(blockAlign == numChannels * bytesPerSample);
//    if (fmttag == 1 /*PCM*/) {
//        switch (bitsPerSample) {
//            case 8:
//                sampleFormat = paInt8;
//                break;
//            case 16:
//                sampleFormat = paInt16;
//                break;
//            case 32:
//                sampleFormat = paInt32;
//                break;
//            default: CHECK(false);
//        }
//        printf("PCM %ibit int\n", bitsPerSample);
//    } else {
//        CHECK(fmttag == 3 /* IEEE float */);
//        CHECK(bitsPerSample == 32);
//        sampleFormat = paFloat32;
//        printf("32bit float\n");
//    }
//    if (chunkLen > 16) {
//        uint16_t extendedSize = freadNum<uint16_t>(wavfile);
//        CHECK(chunkLen == 18 + extendedSize);
//        fseek(wavfile, extendedSize, SEEK_CUR);
//    }
//}
//
//int test2(string path) {
//    wavfile = fopen(path.c_str(), "rb");
//    CHECK(wavfile != NULL);
//
//    CHECK(freadStr(wavfile, 4) == "RIFF");
//    uint32_t wavechunksize = freadNum<uint32_t>(wavfile);
//    CHECK(freadStr(wavfile, 4) == "WAVE");
//    while (true) {
//        std::string chunkName = freadStr(wavfile, 4);
//        uint32_t chunkLen = freadNum<uint32_t>(wavfile);
//        if (chunkName == "fmt ")
//            readFmtChunk(chunkLen);
//        else if (chunkName == "data") {
//            CHECK(sampleRate != 0);
//            CHECK(numChannels > 0);
//            CHECK(bytesPerSample > 0);
//            printf("len: %.0f secs\n", double(chunkLen) / sampleRate / numChannels / bytesPerSample);
//            break; // start playing now
//        } else {
//            // skip chunk
//            CHECK(fseek(wavfile, chunkLen, SEEK_CUR) == 0);
//        }
//    }
//
//    printf("start playing...\n");
//    CHECK(portAudioOpen());
//
//    // wait until stream has finished playing
//    while (Pa_IsStreamActive(stream) > 0)
//        usleep(1000);
//
//    printf("finished\n");
//    fclose(wavfile);
//    Pa_CloseStream(stream);
//    Pa_Terminate();
//}
//
//
////////////////////////////////
//
////
////#include <portaudio.h>
////#include <sndfile.h>
////
////static int
////output_cb(const void *input, void *output, unsigned long frames_per_buffer,
////          const PaStreamCallbackTimeInfo *time_info,
////          PaStreamCallbackFlags flags, void *data) {
////    SNDFILE *file = data;
////
////    /* this should not actually be done inside of the stream callback
////     * but in an own working thread
////     *
////     * Note although I haven't tested it for stereo I think you have
////     * to multiply frames_per_buffer with the channel count i.e. 2 for
////     * stereo */
////    sf_read_short(file, output, frames_per_buffer);
////    return paContinue;
////}
////
////static void
////end_cb(void *data) {
////    printf("end!\n");
////}
////
////#define error_check(err) \
////    do {\
////        if (err) { \
////            fprintf(stderr, "line %d ", __LINE__); \
////            fprintf(stderr, "error number: %d\n", err); \
////            fprintf(stderr, "\n\t%s\n\n", Pa_GetErrorText(err)); \
////            return err; \
////        } \
////    } while (0)
////
////int
////test6() {
////    PaStreamParameters out_param;
////    PaStream *stream;
////    PaError err;
////    SNDFILE *file;
////    SF_INFO sfinfo;
////
////
////    file = sf_open("test\\test.wav", SFM_READ, &sfinfo);
////    printf("%d frames %d samplerate %d channels\n", (int) sfinfo.frames,
////           sfinfo.samplerate, sfinfo.channels);
////
////    /* init portaudio */
////    err = Pa_Initialize();
////    error_check(err);
////
////    /* we are using the default device */
////    out_param.device = Pa_GetDefaultOutputDevice();
////    if (out_param.device == paNoDevice) {
////        fprintf(stderr, "Haven't found an audio device!\n");
////        return -1;
////    }
////
////    /* stero or mono */
////    out_param.channelCount = sfinfo.channels;
////    out_param.sampleFormat = paInt16;
////    out_param.suggestedLatency = Pa_GetDeviceInfo(out_param.device)->defaultLowOutputLatency;
////    out_param.hostApiSpecificStreamInfo = NULL;
////
////    err = Pa_OpenStream(&stream, NULL, &out_param, sfinfo.samplerate,
////                        paFramesPerBufferUnspecified, paClipOff,
////                        output_cb, file);
////    error_check(err);
////
////    err = Pa_SetStreamFinishedCallback(stream, &end_cb);
////    error_check(err);
////
////    err = Pa_StartStream(stream);
////    error_check(err);
//////
//////    printf("Play for 5 seconds.\n");
//////    Pa_Sleep(5000);
//////
//////    err = Pa_StopStream(stream);
//////    error_check(err);
//////
//////    err = Pa_CloseStream(stream);
//////    error_check(err);
//////
//////    sf_close(file);
//////
//////    Pa_Terminate();
////
////    return 0;
////}