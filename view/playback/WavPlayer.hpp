//
// Created by toramisu on 2015/7/29.
//
#pragma once

#include <stdio.h>
#include "string.h"
#include "string"
#include <stdio.h>
#include <portaudio.h>

#define CHECK(x) { if(!(x)) { \
fprintf(stderr, "%s:%i: failure at: %s\n", __FILE__, __LINE__, #x); \
; } }

std::string freadStr(FILE *f, size_t len) {
    std::string s(len, '\0');
    if (fread(&s[0], 1, len, f) == len)
        return s;
}

template<typename T>
T freadNum(FILE *f) {
    T value;
    if (fread(&value, sizeof(value), 1, f) == 1)
        return value; // no endian-swap for now... WAV is LE anyway...
}

int paStreamCallback(
        const void *input, void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo *timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData);

class WavPlayer {
public:
    PaStream *stream;
    FILE *wavfile;
    int numChannels;
    int sampleRate;

    double duration;
    PaSampleFormat sampleFormat;
    int bytesPerSample, bitsPerSample;

    WavPlayer() {

    }

    void seek(int pos) {
    }

    void readFmtChunk(uint32_t chunkLen) {
        CHECK(chunkLen >= 16);
        uint16_t fmttag = freadNum<uint16_t>(wavfile); // 1: PCM (int). 3: IEEE float
        CHECK(fmttag == 1 || fmttag == 3);
        numChannels = freadNum<uint16_t>(wavfile);
        CHECK(numChannels > 0);
        printf("%i channels\n", numChannels);
        sampleRate = freadNum<uint32_t>(wavfile);
        printf("%i Hz\n", sampleRate);
        uint32_t byteRate = freadNum<uint32_t>(wavfile);
        uint16_t blockAlign = freadNum<uint16_t>(wavfile);
        bitsPerSample = freadNum<uint16_t>(wavfile);
        bytesPerSample = bitsPerSample / 8;
        CHECK(byteRate == sampleRate * numChannels * bytesPerSample);
        CHECK(blockAlign == numChannels * bytesPerSample);
        if (fmttag == 1 /*PCM*/) {
            switch (bitsPerSample) {
                case 8:
                    sampleFormat = paInt8;
                    break;
                case 16:
                    sampleFormat = paInt16;
                    break;
                case 32:
                    sampleFormat = paInt32;
                    break;
                default: CHECK(false);
            }
            printf("PCM %ibit int\n", bitsPerSample);
        } else {
            CHECK(fmttag == 3 /* IEEE float */);
            CHECK(bitsPerSample == 32);
            sampleFormat = paFloat32;
            printf("32bit float\n");
        }
        if (chunkLen > 16) {
            uint16_t extendedSize = freadNum<uint16_t>(wavfile);
            CHECK(chunkLen == 18 + extendedSize);
            fseek(wavfile, extendedSize, SEEK_CUR);
        }
    }

    bool portAudioOpen() {
        CHECK(Pa_Initialize() == paNoError);

        PaStreamParameters outputParameters;

        outputParameters.device = Pa_GetDefaultOutputDevice();
        CHECK(outputParameters.device != paNoDevice);

        outputParameters.channelCount = numChannels;
        outputParameters.sampleFormat = sampleFormat;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;

        PaError ret = Pa_OpenStream(
                &stream,
                NULL, // no input
                &outputParameters,
                sampleRate,
                paFramesPerBufferUnspecified, // framesPerBuffer
                0, // flags
                &paStreamCallback,
                this
        );

        if (ret != paNoError) {
            fprintf(stderr, "Pa_OpenStream failed: (err %i) %s\n", ret, Pa_GetErrorText(ret));
            if (stream)
                Pa_CloseStream(stream);
            return false;
        }

//        CHECK(Pa_StartStream(stream) == paNoError);
        return true;
    }

    void load(std::string filename) {
        wavfile = fopen(filename.c_str(), "rb");
//        CHECK(wavfile != NULL);
        if (wavfile != NULL) {

            if (freadStr(wavfile, 4) == "RIFF") {

            }
            uint32_t wavechunksize = freadNum<uint32_t>(wavfile);
            if (freadStr(wavfile, 4) == "WAVE") {
                while (true) {
                    std::string chunkName = freadStr(wavfile, 4);
                    uint32_t chunkLen = freadNum<uint32_t>(wavfile);
                    if (chunkName == "fmt ")
                        readFmtChunk(chunkLen);
                    else if (chunkName == "data") {
                        CHECK(sampleRate != 0);
                        CHECK(numChannels > 0);
                        CHECK(bytesPerSample > 0);
                        duration = double(chunkLen) / sampleRate / numChannels / bytesPerSample;
                        printf("len: %.0f secs\n", duration);
                        break; // start playing now
                    } else {
                        // skip chunk
                        CHECK(fseek(wavfile, chunkLen, SEEK_CUR) == 0);
                    }
                }
                cout << "wav inited..." << endl;
                CHECK(portAudioOpen());
                // wait until stream has finished playing
//                while (Pa_IsStreamActive(stream) > 0)
//                    usleep(1000);
//
//                printf("finished\n");
//                fclose(wavfile);
//                Pa_CloseStream(stream);
//                Pa_Terminate();
            }
        }

    }

    void setVol(int vol) {
    }

    void pause() {
        if (Pa_IsStreamActive(stream))
            Pa_StopStream(stream);
    }

    void play() {
        CHECK(Pa_StartStream(stream) == paNoError);
    }

    void close1() {
        fclose(wavfile);
        Pa_CloseStream(stream);
        Pa_Terminate();
    }
};

int paStreamCallback(
        const void *input, void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo *timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData) {

    WavPlayer *wavPlayer = (WavPlayer *) userData;
    size_t numRead = fread(output, wavPlayer->bytesPerSample * wavPlayer->numChannels, frameCount, wavPlayer->wavfile);
    output = (uint8_t *) output + numRead * wavPlayer->numChannels * wavPlayer->bytesPerSample;
//    frameCount -= numRead;
    frameCount -= numRead;

    if (frameCount > 0) {
        memset(output, 0, frameCount * wavPlayer->numChannels * wavPlayer->bytesPerSample);
        return paComplete;
    }

    return paContinue;
}