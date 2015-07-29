//
// Created by toramisu on 2015/7/29.
//
#pragma once

#include "VsObj.hpp"

class TextField : public VsObj {
public:
    TextField() {
    }

    void setText(string t) {
        _text = t;
    }

    void setColor(NVGcolor col) {
        _col = col;
    }

    void setFontSize(int size) {
        _fontSize = size;
    }

protected:
    virtual void render() override {
        nvgFontFace(vg, "sans");
        nvgFontSize(vg, _fontSize);
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgFillColor(vg, _col);
        nvgText(vg, gX(), gY(), _text.c_str(), nullptr);
        VsObj::render();
    }

private:
    string _text;
    NVGcolor _col = nvgRGB(240, 240, 240);
    float _fontSize = 14.0f;
};

