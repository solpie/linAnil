//
// Created by toramisu on 2015/7/30.
//
#pragma once


#include "Sndfile.hpp"


//#include "view/playback/FFmpegTest.hpp"

//#include "view/playback/AudioPlayer.hpp"
#include "view/playback/AudioPlayback.hpp"
void testMain() {
//    ffmain();

//    AudioPlayer *a = new AudioPlayer;
//    a->load("test\\test.wav");
//    a->play();

//    testSnd();

    AudioPlayback *audioPlayback = new AudioPlayback;
    audioPlayback->load("test\\test.wav");
    audioPlayback->play();
}
