//
// Created by toramisu on 2015/7/30.
//
#pragma once

#include "string"
#include "PlaybackState.hpp"

class BasePlayback {
public:
    std::string filename;
    //sec
    double duration;
    //sec
    double position;

    BasePlayback() {

    }

    int getState() {
        return _state;
    }

    void play() {
        if (_state == PlaybackState::PAUSE || _state == PlaybackState::STOP) {
            _state = PlaybackState::PLAY;
            _onPlay();
        }
    }

    void pause() {
        if (_state == PlaybackState::PLAY) {
            _state = PlaybackState::PAUSE;
            _onPause();
        }
    }


    void stop() {
        if (_state == PlaybackState::PLAY) {
            _state = PlaybackState::STOP;
            _onStop();
        }
    }

    void toggle() {
        if (_state == PlaybackState::PLAY) {
            pause();
        }
        else if (_state == PlaybackState::STOP || _state == PlaybackState::PAUSE) {
            play();
        }
    }

    virtual void seek(double position) {

    }

protected:
    virtual void _onPlay() {

    }

    virtual void _onPause() {

    }

    virtual void _onStop() {

    }

private:
    int _state = PlaybackState::STOP;

};