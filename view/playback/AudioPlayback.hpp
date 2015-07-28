//
// Created by toramisu on 2015/7/28.
//

#pragma once

#include "AL/al.h"
#include "AL/alc.h"
#include "stdio.h"
#include <cstdio>
#include <math.h> // for cosf
#include <limits>

class AudioPlayback {
public:
    AudioPlayback() {
        InitOpenAL(); // ��ʼ��openal
        LoadData(); // ����WAV����
        Play(); // ����
        UnloadData(); // ж��WAV����
        ShutdownOpenAL(); // �ر�openal
    }

    bool InitOpenAL() {
        ALCdevice *pDevice = alcOpenDevice(NULL);  // ��Ĭ����Ƶ�豸
        ALCcontext *pContext = alcCreateContext(pDevice, NULL);
        alcMakeContextCurrent(pContext);
        return true;
        // ע�⣺����û�н���ʧ�ܼ�⣬������ʾ��
    }

    void ShutdownOpenAL() {
        ALCcontext *pContext;
        ALCdevice *pDevice;

        pContext = alcGetCurrentContext();
        pDevice = alcGetContextsDevice(pContext);

        alcMakeContextCurrent(NULL);
        alcDestroyContext(pContext);
        alcCloseDevice(pDevice);
    }

    bool LoadData() {
        // �������.
        const ALsizei size = 800;
        ALsizei freq = 8000;
        ALboolean loop = 1; // ѭ������
        // ʹ��һ�����Ҳ�������
        short data[800];
        alGenBuffers(1, &Buffer);
        float max = 4 / 4;
        float rad = 0;
        for (short &e : data) {
            e = (short) (max * cosf(rad));
            rad += 1.f;
        }

        // ����WAV����
        alBufferData(Buffer, AL_FORMAT_MONO16, data, size, freq);
        alGenSources(1, &Source);

        // Դ������λ��
        ALfloat SourcePos[] = {0.0, 0.0, 0.0};
        // Դ�������ٶ�
        ALfloat SourceVel[] = {0.0, 0.0, 0.0};

        alSourcei(Source, AL_BUFFER, Buffer);
        alSourcef(Source, AL_PITCH, 1.0f);
        alSourcef(Source, AL_GAIN, 1.0f);
        alSourcefv(Source, AL_POSITION, SourcePos);
        alSourcefv(Source, AL_VELOCITY, SourceVel);
        alSourcei(Source, AL_LOOPING, loop);

        return true;
    }

    void UnloadData() {
        alDeleteBuffers(1, &Buffer);
        alDeleteSources(1, &Source);
    }

    void Play() {
        // ����
        alSourcePlay(Source);
        printf("Press Enter To Stop Sound\n");
        getchar();
        alSourceStop(Source);
    }

    ALuint Source;
    // ���ڲ�������
    ALuint Buffer;// ��������
};