//
// Created by toramisu on 2015/7/17.
//
#include "Sprite.hpp"

class TimestampBar : public Sprite {
public:
    TimestampBar() {
        height = 35;
    }


    virtual void onDraw() override {
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, nvgRGB(47, 47, 47));
        nvgFill(vg);
        VS_RENDER_CHILDREN();
    }

    void resize(int w, int h) {
        width = w;
    }
};

