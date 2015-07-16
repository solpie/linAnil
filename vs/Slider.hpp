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
        add_event(MouseEvent::DOWN, onDown);
        add_event(MouseEvent::UP, onUp);
        Evt_add(VsEvent::STAGE_MOUSE_UP, onUp);
    }

    void onUp(void *e) {
        if (isPress) {
            isPress = false;
            int px = VS_CONTEXT.cursor.x;
            limit(px,gX(),gX()+width)
            glfwSetCursorPos(VS_CONTEXT.window, px, gY() + 5);
            glfwSetInputMode(VS_CONTEXT.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }


    }

//    pos hidePos;
    void onDown(void *e) {
        isPress = true;
        updateValueByPos();
        glfwSetInputMode(VS_CONTEXT.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    virtual void onDraw() override {
        if (isPress)
            updateValueByPos();
        NVGcontext *vg = this->nvgContext;
        int tx = _value * width / maxValue;

        nvgBeginPath(vg);
//        nvgRect(vg, gX(), gY(), width, height);
        nvgRect(vg, gX()+tx-1, gY(), width-tx-1, height);
//        nvgFillColor(vg, nvgRGBA(255, 0, 0, 255));
        nvgFillColor(vg, nvgRGBA(62, 62, 62, 255));
        nvgFill(vg);

        //thumb

        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), tx, height);
        nvgFillColor(vg, nvgRGBA(207, 207, 207, 255));
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

    void setValue(int v) { _value = v; }

private:
    bool isPress = false;

    void updateValueByPos() {
        int px = VS_CONTEXT.cursor.x - gX();
        limit(px,0,width)
        _value = px * (maxValue - minValue + 1) / width;
    }

};

