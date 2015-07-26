#pragma once
//
// Created by manoyuria on 2015/6/19.
//

#ifndef SEQTRUAN_SEQQUENCEPLAYBACK_H
#define SEQTRUAN_SEQQUENCEPLAYBACK_H


#include <events/PlaybackEvent.hpp>
#include <events/SequencePlaybackEvent.hpp>
#include "QTimer"
#include "events/Event.hpp"
#include "events/ActionEvent.hpp"
class SequencePlayback {
public:
    SequencePlayback() {
        frameRate = 24;
        frameIdx = 1;
        state = PlaybackEvent::STOP;
//        state = new string("stop");
        timer = new QTimer();
        setFramerate(24);
        Evt_add(ActionEvent::UPDATE_CURSOR, onUpdateCursor);
    }

    int frameIdx;
    std::string state;
    int endFrameIdx;

    void setFramerate(int frameRate) {
        this->frameRate = frameRate;
        this->timer->setInterval(1000 / this->frameRate);
        timer->connect(timer, QTimer::timeout, [this] {
            frameIdx = (frameIdx + 1) % endFrameIdx;
            update();
        });
//        Evt_dis(SequencePlaybackEvent::FRAME_RATE, e);
    }

    int getFramerate() {
        return frameRate;
    }

    void update() {
        SequencePlaybackEvent *e = new SequencePlaybackEvent();
        e->frameIdx = frameIdx;
        Evt_dis(SequencePlaybackEvent::RENDER_FRAME, e)
    }

    void togglePlay() {
        if (state == PlaybackEvent::PLAY) {
            pause();
            setState(PlaybackEvent::PAUSE);
        }
        else if (state == PlaybackEvent::PAUSE || state == PlaybackEvent::STOP) {
            play();
            setState(PlaybackEvent::PLAY);
        }
    }

    void setState(string newstate) {
        if (state != newstate) {
            state = newstate;
        }
        SequencePlaybackEvent *e = new SequencePlaybackEvent();
        e->state = state;
        Evt_dis(SequencePlaybackEvent::STATE, e);
    }

    void play() {
        if (!timer->isActive()) {
            timer->start();
        }
    }

    void pause() {
        if (timer->isActive()) {
            timer->stop();
        }
    }

    void stop() {
        if (timer->isActive()) {
            timer->stop();
        }
        frameIdx = 1;
    }

protected:
    int frameRate;

private:

    void onUpdateCursor(int *fIdx) {
        this->frameIdx = *fIdx;
        SequencePlaybackEvent *e = new SequencePlaybackEvent();
        e->frameIdx = this->frameIdx;
        Evt_dis(SequencePlaybackEvent::RENDER_FRAME, e)
    }

    QTimer *timer;

};


#endif //SEQTRUAN_SEQQUENCEPLAYBACK_H
