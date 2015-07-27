//
// Created by toramisu on 2015/7/27.
//

#pragma once

#include "BaseTrackInfo.hpp"
#include "vector"
#include "AL/al.h"
#include "AL/alc.h"

struct RIFF_Header {
    char chunkID[4];
    long chunkSize;
    char format[4];
};

struct WAVE_Format {
    char subChunkID[4];
    long subChunkSize;
    short audioFormat;
    short numChannels;
    long sampleRate;
    long byteRate;
    short blockAlign;
    short bitsPerSample;
};

struct WAVE_Data {
    char subChunkID[4];
    long subChunk2Size;
};

class AudioTrackInfo : public BaseTrackInfo {
public:
    AudioTrackInfo(std::string n, int t) : BaseTrackInfo(n, t) {
        samples = new vector <float>;
    }

    vector <float> *samples;

    bool loadWavFile(const char *filename, ALuint *buffer,
                     ALsizei *size, ALsizei *frequency,
                     ALenum *format) {
        FILE *soundFile = NULL;
        WAVE_Format wave_format;
        RIFF_Header riff_header;
        WAVE_Data wave_data;
        unsigned char *data;

        try {
            soundFile = fopen(filename, "rb");
            if (!soundFile)
                throw (filename);

            fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

            if ((riff_header.chunkID[0] != 'R' ||
                 riff_header.chunkID[1] != 'I' ||
                 riff_header.chunkID[2] != 'F' ||
                 riff_header.chunkID[3] != 'F') &&
                (riff_header.format[0] != 'W' ||
                 riff_header.format[1] != 'A' ||
                 riff_header.format[2] != 'V' ||
                 riff_header.format[3] != 'E'))
                throw ("Invalid RIFF or WAVE Header");

            fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);

            if (wave_format.subChunkID[0] != 'f' ||
                wave_format.subChunkID[1] != 'm' ||
                wave_format.subChunkID[2] != 't' ||
                wave_format.subChunkID[3] != ' ')
                throw ("Invalid Wave Format");

            if (wave_format.subChunkSize > 16)
                fseek(soundFile, sizeof(short), SEEK_CUR);

            fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);

            if (wave_data.subChunkID[0] != 'd' ||
                wave_data.subChunkID[1] != 'a' ||
                wave_data.subChunkID[2] != 't' ||
                wave_data.subChunkID[3] != 'a')
                throw ("Invalid data header");

            data = new unsigned char[wave_data.subChunk2Size];

            if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
                throw ("error loading WAVE data into struct!");

            *size = wave_data.subChunk2Size;
            *frequency = wave_format.sampleRate;

            if (wave_format.numChannels == 1) {
                if (wave_format.bitsPerSample == 8)
                    *format = AL_FORMAT_MONO8;
                else if (wave_format.bitsPerSample == 16)
                    *format = AL_FORMAT_MONO16;
            } else if (wave_format.numChannels == 2) {
                if (wave_format.bitsPerSample == 8)
                    *format = AL_FORMAT_STEREO8;
                else if (wave_format.bitsPerSample == 16)
                    *format = AL_FORMAT_STEREO16;
            }

            alGenBuffers(1, buffer);
            alBufferData(*buffer, *format, (void *) data,
                         *size, *frequency);
            fclose(soundFile);
            return true;
        } catch (char *error) {
            if (soundFile != NULL)
                fclose(soundFile);
            return false;
        }
    }

};

int main1(){

    //Sound play data
    ALint state;                            // The state of the sound source
    ALuint bufferID;                        // The OpenAL sound buffer ID
    ALuint sourceID;                        // The OpenAL sound source
    ALenum format;                          // The sound data format
    ALsizei freq;                           // The frequency of the sound data
    ALsizei size;                           // Data size

    ALCdevice* device = alcOpenDevice(NULL);
    ALCcontext* context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    // Create sound buffer and source
    alGenBuffers(1, &bufferID);
    alGenSources(1, &sourceID);

    // Set the source and listener to the same location
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(sourceID, AL_POSITION, 0.0f, 0.0f, 0.0f);

    loadWavFile("..\\wavdata\\YOURWAVHERE.wav", &bufferID, &size, &freq, &format);

    alSourcei(sourceID, AL_BUFFER, bufferID);

    alSourcePlay(sourceID);

    do{
        alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
    } while (state != AL_STOPPED);


    alDeleteBuffers(1, &bufferID);
    alDeleteSources(1, &sourceID);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}