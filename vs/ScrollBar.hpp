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

    ScrollBar(int dir) {
        _dir = dir;

        add_event(MouseEvent::DOWN, onDown);
        add_event(MouseEvent::UP, onUp);
        add_event_on_context(MouseEvent::UP, onUp);
    }

    void onUp(void *e) {
        _isPress = false;
    }

    void onDown(void *e) {
        _isPress = true;
        _lastX = _lastY = 0;
    }

    void updateValueByPos() {
//        int px = VS_CONTEXT.cursor.x - gX();
//        if (px < 0)
//            px = 0;
//        else if (px > width)
//            px = width;
//        _value = px * (_maxValue - minValue + 1) / width;
    }

    virtual void onDraw() override {
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, _3RGB(47));
        nvgFill(vg);

        //thumb
//        int tx = _value * width / _maxValue;

        if (_isHorizontal()) {
//            nvgBeginPath(vg);
//            nvgRect(vg, gX() + tx, gY() - 1, 5, height + 2);
//            nvgFillColor(vg, nvgRGB(44, 44, 44));
//            nvgFill(vg);
//
//            nvgBeginPath(vg);
//            nvgRect(vg, gX() + tx + 1, gY(), 3, height);
//            nvgFillColor(vg, nvgRGB(207, 207, 207));
//            nvgFill(vg);
//
//            nvgBeginPath(vg);
//            nvgRect(vg, gX() + tx + 2, gY() + 1, 1, height - 2);
//            nvgFillColor(vg, nvgRGB(182, 182, 182));
//            nvgFill(vg);
        }
        else {
            if (_isPress) {
                int cY = VS_CONTEXT.cursor.y;
                int dy = 0;
                if (_lastY)
                    dy = cY - _lastY;
                _lastY = cY;
                if (dy != 0) {
                    _value += dy;
                    if (_maxValue > 0) limit(_value, 0, _maxValue)
                    if (_value >= 0)
                        disEvent(VsEvent::CHANGED);
                }
            }
            if (_value < 0)
                _value = 0;
            nvgBeginPath(vg);
            nvgRect(vg, gX(), gY() + _value, width, _barLength);
            nvgFillColor(vg, _3RGB(88));
            nvgFill(vg);
        }
        ////

    }

    void setContent(EventDispatcher *e) {
        add_event_on(e, VsEvent::RESIZE, onContentResize);
    }

    void setContent(int v) {
        _contentLength = v;
        if (_isHorizontal()) {
            _barLength = width * width / _contentLength;
            _maxValue = width - _barLength;


        }
        else {
            _barLength = height * height / _contentLength;
            _maxValue = height - _barLength;

        }
    }


    virtual void setSize(int w, int h) override {
        VsObj::setSize(w, h);
        setContent(_contentLength);
    }

    int getValue() { return _value; }

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

    int _maxValue = 100;

    int _barLength = 0;
    int _dir = 1;
    int _contentLength = 0;
    bool _isPress = false;
    int _lastX, _lastY;
    int _value = 0;

};
