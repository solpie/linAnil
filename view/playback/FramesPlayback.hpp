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
        Evt_add(PlaybackEvent::STOP, onStop)
        Evt_add(PlaybackEvent::FORWARD, onForward)
        Evt_add(PlaybackEvent::BACKWARD, onBackward)
    }

    void play() {
        init();
        _lastStopFrame = _proj->curCompInfo->getCurrentFrame();
        timer->start();
        state = PlaybackState::PLAY;
    }

    void pause() {
        timer->stop();
        state = PlaybackState::PAUSE;
    }

    void stop() {
        pause();
        _projInfo->curCompInfo->setCurrentFrame(_lastStopFrame);
    }
    int state = PlaybackState::PAUSE;
private:
    int _lastStopFrame=1;
    void onStop(void *e) {
        stop();
    }
    void onForward(void *e) {
        _lastStopFrame = _proj->curCompInfo->getCurrentFrame();
        _projInfo->curCompInfo->increaseCurrentFrame();
    }

    void onBackward(void *e) {
        _lastStopFrame = _proj->curCompInfo->getCurrentFrame();
        _projInfo->curCompInfo->decreaseCurrentFrame();
    }

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