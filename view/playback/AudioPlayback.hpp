//
// Created by toramisu on 2015/7/28.
//

#pragma once

#include <portaudio.h>
#include <string>
#include <sndfile.h>
#include "BasePlayback.hpp"

int _paCallBack(const void *input,
                void *output,
                unsigned long frameCount,
                const PaStreamCallbackTimeInfo *paTimeInfo,
                PaStreamCallbackFlags statusFlags,
                void *userData);

class AudioPlayback : public BasePlayback {
public:

    SNDFILE *sndFile;
    SF_INFO sfInfo;
    int positionFrame;
    PaStream *stream;

    std::string filename;

    AudioPlayback() {
    }

    void load(std::string path) {
        if (!_isInit) {

            filename = path;
            init();
        }
    }

    void init() {
        PaError error;
        PaStreamParameters outputParameters;
        /* initialize our data structure */
        this->positionFrame = 0;
        this->sfInfo.format = 0;
        /* try to open the file */
        this->sndFile = sf_open(filename.c_str(), SFM_READ, &this->sfInfo);

        if (!this->sndFile) {
            printf("error opening file\n");
            return;
        }

        duration = sfInfo.frames / sfInfo.samplerate;


        /* start portaudio */
        Pa_Initialize();
        /* set the output parameters */
        /* use the default device */
        outputParameters.device = Pa_GetDefaultOutputDevice();
        /* use the same number of channels as our sound file */
        outputParameters.channelCount = this->sfInfo.channels;
//        sfInfo.format
        /* 32bit int format */
        outputParameters.sampleFormat = paInt32;
        /* 200 ms ought to satisfy even the worst sound card */
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = 0; /* no api specific data */

        /* try to open the output */
        error = Pa_OpenStream(&stream,  /* stream is a 'token' that we need to save for future portaudio calls */
                              0,  /* no input */
                              &outputParameters,
                              sfInfo.samplerate,  /* use the same sample rate as the sound file */
                              paFramesPerBufferUnspecified,  /* let portaudio choose the buffersize */
                              paNoFlag,  /* no special modes (clip off, dither off) */
                              _paCallBack,  /* callback function defined above */
                              this); /* pass in our data structure so the callback knows what's up */

        /* if we can't open it, then bail out */
        if (error) {
            printf("error opening output, error code = %i\n", error);
            Pa_Terminate();
            return;
        }
        _isInit = true;
    }


    virtual void seek(double position) override {
        if (_isInit) {
            positionFrame = position / duration * sfInfo.frames;
        }
    }

protected:
    virtual void _onPlay() override {
        BasePlayback::_onPlay();
        if (_isInit) {
            /* when we start the stream, the callback starts getting called */
            Pa_StartStream(stream);
        }
    }


private:
    bool _isInit = false;
};


/*
Callback function for audio output
*/
int _paCallBack(const void *input,
                void *output,
                unsigned long frameCount,
                const PaStreamCallbackTimeInfo *paTimeInfo,
                PaStreamCallbackFlags statusFlags,
                void *userData) {
    AudioPlayback *data = (AudioPlayback *) userData; /* we passed a data structure
into the callback so we have something to work with */
    int *cursor; /* current pointer into the output  */
    int *out = (int *) output;
    int thisSize = frameCount;
    int thisRead;

    cursor = out; /* set the output cursor to the beginning */
    while (thisSize > 0) {

        /* seek to our current file positionFrame */
        sf_seek(data->sndFile, data->positionFrame, SEEK_SET);

        /* are we going to read past the end of the file?*/
        if (thisSize > (data->sfInfo.frames - data->positionFrame)) {
            /*if we are, only read to the end of the file*/
            thisRead = data->sfInfo.frames - data->positionFrame;
            /* and then loop to the beginning of the file */
            data->positionFrame = 0;
        }
        else {
            /* otherwise, we'll just fill up the rest of the output buffer */
            thisRead = thisSize;
            /* and increment the file positionFrame */
            data->positionFrame += thisRead;
        }

        /* since our output format and channel interleaving is the same as
    sf_readf_int's requirements */
        /* we'll just read straight into the output buffer */
        sf_readf_int(data->sndFile, cursor, thisRead);
        /* increment the output cursor*/
        cursor += thisRead;
        /* decrement the number of samples left to process */
        thisSize -= thisRead;
    }

    return paContinue;
}
