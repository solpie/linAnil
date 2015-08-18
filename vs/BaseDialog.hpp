//
// Created by toramisu on 2015/8/18.
//
#pragma once


#include "Sprite.hpp"

class BaseDialog : public Sprite {
public:
    BaseDialog() {
        width = 420;
        height = 185;
    }

    void setText(const char *text) {
        _text = text;
    }

    void setTitle(const char *title) {
        _title = title;
    }

protected:
    const char *_text = nullptr;
    const char *_title = nullptr;

    virtual void onDraw() override {


        fillRect(_3RGB(22), gX(), gY(), width, height)

        fillRect(nvgRGB(250, 240, 20), gX(), gY() + 25, width, 3)


        //title
        if (_title) {
            nvgFontFace(vg, "sans");
            nvgFontSize(vg, 14.0f);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, _3RGB(240));
            nvgText(vg, gX() + 5, gY() + 5, _title, nullptr);
        }

        if (_text) {
            nvgFontFace(vg, "sans");
            nvgFontSize(vg, 16.0f);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, _3RGB(240));
            nvgText(vg, gX() + 15, gY() + 35, _text, nullptr);
        }


        VS_RENDER_CHILDREN();
    }
};

