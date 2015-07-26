#pragma once
//
// Created by manoyuria on 2015/7/25.
//

#include <GLFW/glfw3.h>
#include <vs/utils/VsTimer.hpp>
#include <vs/events/TimerEvent.hpp>

#ifndef LINANIL_FRAMEPLAYBACK_HPP
#define LINANIL_FRAMEPLAYBACK_HPP

#endif //LINANIL_FRAMEPLAYBACK_HPP

class FramesPlayback {
public:
    FramesPlayback(ProjectInfo *projInfo) {
        _projInfo = projInfo;
    }

    void start() {
        init();
        timer->start();
    }

    void stop() {
        timer->stop();
    }

    int state = 0;
    int frameRate;
    int curFrameIdx;
private:
    void init() {
        if (!timer) {
            if (_projInfo->curCompInfo) {
                timer = new VsTimer(_projInfo->curCompInfo->frameRate);
                add_event_on(timer, TimerEvent::TICK, onTick)
            }
        }
    }

    void onTick(void *e) {
        ++_projInfo->curCompInfo->currentFrame;
    }

    ProjectInfo *_projInfo;
    VsTimer *timer= nullptr;
};