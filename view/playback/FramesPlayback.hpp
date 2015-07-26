#pragma once
//
// Created by manoyuria on 2015/7/25.
//

#include <GLFW/glfw3.h>
#include <vs/utils/VsTimer.hpp>
#include <vs/events/TimerEvent.hpp>
#include <events/PlaybackEvent.hpp>

#ifndef LINANIL_FRAMEPLAYBACK_HPP
#define LINANIL_FRAMEPLAYBACK_HPP

#endif //LINANIL_FRAMEPLAYBACK_HPP

#include "PlaybackState.hpp"

class FramesPlayback {
public:
    FramesPlayback(ProjectInfo *projInfo) {
        _projInfo = projInfo;
        Evt_add(PlaybackEvent::TOGGLE, onToggle)
    }

    void play() {
        init();
        timer->start();
        state = PlaybackState::PLAY;
    }

    void pause() {
        timer->stop();
        state = PlaybackState::PAUSE;
    }

    void stop() {
        pause();
        curFrameIdx = 1;
    }

    int state = PlaybackState::PAUSE;
    int frameRate;
    int curFrameIdx;
private:
    void onToggle(void *e) {
        if (state == PlaybackState::PAUSE) {
            play();
        }
        else if (state == PlaybackState::PLAY) {
            pause();
        }
    }

    void init() {
        if (!timer) {
            if (_projInfo->curCompInfo) {
                timer = new VsTimer(_projInfo->curCompInfo->frameRate);
                add_event_on(timer, TimerEvent::TICK, onTick)
            }
        }
    }

    void onTick(void *e) {
        _projInfo->curCompInfo->increaseCurrentFrame();
    }

    ProjectInfo *_projInfo;
    VsTimer *timer = nullptr;
};