#pragma once
//
// Created by manoyuria on 2015/7/25.
//

#ifndef LINANIL_VSTIMER_HPP
#define LINANIL_VSTIMER_HPP

#endif //LINANIL_VSTIMER_HPP

#include <thread>

#include <GLFW/glfw3.h>
#include <iostream>
#include "events/EventDispatcher.hpp"

class Busy {
public:
    bool isBusy() {

    }

private:

};

void run() {

}

class VsTimer : public EventDispatcher {
public:
    VsTimer(int delay, bool isThread = false) {
        _isThread = isThread;
        setDelay(delay);
    }

    void start() {
        _isBusy = true;
        _tickCount = 0;
        if (_isThread) {
            std::thread t([this] { _run(); });
            t.detach();
        }
        else {
            if (!_hasListener) {
                _hasListener = true;
                VS_CONTEXT.add(VsEvent::RENDER, [this](void *e) { _onRender(); });
            }
            _lastFrameTime = 0;
        }
    }

    void stop() {
        _isBusy = false;
    }

    bool isBusy() {
        return _isBusy;
    }

    void setDelay(int delay) {
        _delay = delay;
        _delayInSec = double(delay) / 1000;
    }

private:
    double _lastFrameTime;
    int _tickCount = 0;

    void _onRender() {
        _lastFrameTime += VS_CONTEXT.getFrameTime();
        if (_lastFrameTime > _delayInSec) {
            ++_tickCount;
//            cout << typeid(this).name() << "sec " <<_tickCount<< endl;
            _lastFrameTime = _delayInSec - _lastFrameTime;
        }
    }

    void _run() {
        while (_isBusy) {
            this_thread::sleep_for(chrono::milliseconds(_delay));
//            if (_lastTime) {
//                double dt = glfwGetTime() - _lastTime;
//                cout << typeid(this).name() << "dt " << dt << endl;
//            }
//            else
//                _lastTime = glfwGetTime();
            cout << typeid(this).name() << "second " << endl;

        }
    }

    bool _hasListener = false;
    bool _isThread = false;
    bool _isBusy = false;

    int _delay = 0;
    double _delayInSec = 0;
    double _lastTime = 0;
};