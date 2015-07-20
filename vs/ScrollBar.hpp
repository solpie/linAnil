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
        nvgFillColor(vg, _3RGB(47));
        nvgFill(vg);

        //thumb
        int tx = _value * width / maxValue;

        if (_isHorizontal()) {
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
            nvgRect(vg, gX(), gY() + tx, width, _barLength);
            nvgFillColor(vg, _3RGB(88));
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

    void setContent(EventDispatcher *e) {
        add_event_on(e, VsEvent::RESIZE, onContentResize);
    }

    void setContent(int v) {
        _contentLength = v;
        if (_isHorizontal()) {
            _barLength = width * width / _contentLength;

        }
        else {
            _barLength = height * height / _contentLength;
        }
    }


    virtual void setSize(int w, int h) override {
        Sprite::setSize(w, h);
        setContent(_contentLength);
    }

private:
    void onContentResize(void *e) {
        VsObj *v = get_dispatcher(VsObj);
        if (_isHorizontal())
            setContent(v->width);
        else
            setContent(v->height);
    }

    bool _isHorizontal() {
        return _dir == Direction::Horizontal;
    }

    int _barLength = 0;
    int _dir = 1;
    int _contentLength = 0;
    bool isPress = false;
    int _value = 0;

};
