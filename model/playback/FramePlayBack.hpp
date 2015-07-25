#pragma once
//
// Created by manoyuria on 2015/7/25.
//

#include <GLFW/glfw3.h>

#ifndef LINANIL_FRAMEPLAYBACK_HPP
#define LINANIL_FRAMEPLAYBACK_HPP

#endif //LINANIL_FRAMEPLAYBACK_HPP

class FramePlayBack {
public:
    FramePlayBack() {

    }

    void start() {
        if(_lastTime)
        double t = glfwGetTime();

    }

    int frameRate;
    int curFrameIdx;
private:
    double _lastTime = 0;
};