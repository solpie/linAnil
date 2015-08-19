//
// Created by toramisu on 2015/8/19.
//
#pragma once

#include "Sprite.hpp"

class Button : public Sprite {
public:
    Button(const char *text) {
        width = 75;
        height = 30;
        _text = text;
    }


protected:
    virtual void onDraw() override {
        fillRect(nvgRGB(120, 120, 120), gX(), gY(), width, height)
        if (_text) {
            nvgFontFace(vg, "sans");
            nvgFontSize(vg, 16.0f);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, _3RGB(240));
            nvgText(vg, gX() + 15, gY() + 5, _text, nullptr);
        }
    }

    const char *_text = nullptr;

};
