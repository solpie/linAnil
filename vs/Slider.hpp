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
        addEvent(MouseEvent::DOWN, onDown);
        addEvent(MouseEvent::UP, onUp);
        Evt_add(ActionEvent::STAGE_MOUSE_UP, onUp);
    }


    void onUp(void *e) {
        if (isPress)
            isPress = false;
    }


    void onDown(MouseEvent *e) {
        isPress = true;
        updateValueByPos();
    }

    virtual void onDraw() override {
        if (isPress)
            updateValueByPos();
        NVGcontext *vg = this->nvgContext;
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, nvgRGBA(62, 62, 62, 255));
        nvgFill(vg);

        //thumb
        int tx = _value * width / maxValue;
        nvgBeginPath(vg);
        nvgRect(vg, gX() + tx, gY() - 1, 5, height + 2);
        nvgFillColor(vg, nvgRGBA(44, 44, 44, 255));
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgRect(vg, gX() + tx + 1, gY(), 3, height);
        nvgFillColor(vg, nvgRGBA(207, 207, 207, 255));
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgRect(vg, gX() + tx + 2, gY() + 1, 1, height - 2);
        nvgFillColor(vg, nvgRGBA(182, 182, 182, 255));
        nvgFill(vg);
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

    int maxValue = 100;
    int minValue = 0;
    int _value = 0;

    int getValue() {
        return _value;
    }

private:
    bool isPress = false;

    void updateValueByPos() {
        int px = VS_CONTEXT.cursor.x - gX();
        if (px < 0)
            px = 0;
        else if (px > width)
            px = width;
        _value = px * (maxValue - minValue + 1) / width;
    }

};

