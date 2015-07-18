#pragma once
//
// Created by manoyuria on 2015/7/15.
//

#ifndef LINANIL_SCROLLBAR_HPP
#define LINANIL_SCROLLBAR_HPP

#endif //LINANIL_SCROLLBAR_HPP

#include "Sprite.hpp"

class ScrollBar : public Sprite {
public:
    int maxValue = 100;
    int minValue = 0;
    int _value = 0;

    ScrollBar(int dir) {
        _dir = dir;
    }

    void updateValueByPos() {
        int px = VS_CONTEXT.cursor.x - gX();
        if (px < 0)
            px = 0;
        else if (px > width)
            px = width;
        _value = px * (maxValue - minValue + 1) / width;
    }

    virtual void onDraw() override {
        if (isPress)
            updateValueByPos();
//        NVGcontext *vg = this->vg;
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, nvgRGB(62, 62, 62));
        nvgFill(vg);

        //thumb
        int tx = _value * width / maxValue;

        if (_dir == Direction::Horizontal) {
            nvgBeginPath(vg);
            nvgRect(vg, gX() + tx, gY() - 1, 5, height + 2);
            nvgFillColor(vg, nvgRGB(44, 44, 44));
            nvgFill(vg);

            nvgBeginPath(vg);
            nvgRect(vg, gX() + tx + 1, gY(), 3, height);
            nvgFillColor(vg, nvgRGB(207, 207, 207));
            nvgFill(vg);

            nvgBeginPath(vg);
            nvgRect(vg, gX() + tx + 2, gY() + 1, 1, height - 2);
            nvgFillColor(vg, nvgRGB(182, 182, 182));
            nvgFill(vg);
        }
        else {
            nvgBeginPath(vg);
//            nvgRect(vg, gX() + tx, gY() - 1, 5, height + 2);
            nvgRect(vg, gX() - 1, gY() + tx, width + 2, 5);
            nvgFillColor(vg, nvgRGB(44, 44, 44));
            nvgFill(vg);

            nvgBeginPath(vg);
//            nvgRect(vg, gX() + tx + 1, gY(), 3, height);
            nvgRect(vg, gX(), gY() + tx + 1, width,3);
            nvgFillColor(vg, nvgRGB(207, 207, 207));
            nvgFill(vg);

            nvgBeginPath(vg);
//            nvgRect(vg, gX() + tx + 2, gY() + 1, 1, height - 2);
            nvgRect(vg, gX()  + 1, gY()+ tx + 2, width-2,1);
            nvgFillColor(vg, nvgRGB(182, 182, 182));
            nvgFill(vg);
        }
        ////

        //value hint
        char str[4];
        if (isPress) {
            nvgFontFace(vg, "sans");
            nvgFontSize(vg, 14.0f);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, nvgRGBA(240, 240, 240, 192));
            sprintf(str, "%d%%", _value * 100 / (maxValue - minValue + 1));
            nvgText(vg, gX() + tx, gY() - 20, str, nullptr);
        }

    }

private:
    int _dir = 1;

    bool isPress = false;

};