//
// Created by toramisu on 2015/7/12.
//
#pragma once
#ifndef LINANIL_SLIDER_HPP
#define LINANIL_SLIDER_HPP

#endif //LINANIL_SLIDER_HPP

#include "Sprite.hpp"

class Slider : public Sprite {
public:
    Slider(bool isHorizontal = true) {
        width = 80;
        height = 15;
    }

    virtual void onDraw() override {
        NVGcontext *vg = this->nvgContext;
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, nvgRGBA(62, 62, 62, 255));
        nvgFill(vg);
    }
};

