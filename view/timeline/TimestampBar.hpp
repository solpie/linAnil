//
// Created by toramisu on 2015/7/17.
//
#include "Sprite.hpp"

class TimestampBar : public Sprite {
public:
    TimestampBar() {
        height = 45;
        add_event(MouseEvent::DOWN, onDown);
        add_event(MouseEvent::UP, onUp);
    }

    void onUp(void *e) {
        isPressScrollBar = false;
    }

    void onDown(void *e) {
        cout << this << " mouseX: " << mouseX();
        if (mouseY() < scrollBarHeight) {
            isPressScrollBar = true;
        }
        else {
            isPressScrollBar = false;
        }
    }

    virtual void onDraw() override {
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, nvgRGB(47, 47, 47));
        nvgFill(vg);

        //scroll bar
        int barWidth = float(maxValue - width) / stepValue;
        int barX = float(_value) / stepValue;
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), barWidth, scrollBarHeight);
        nvgFillColor(vg, nvgRGB(88, 88, 88));
        nvgFill(vg);


        VS_RENDER_CHILDREN();
    }

    void resize(int w, int h) {
        width = w;
    }

    int _value = 0;
    int maxValue = 2048;
    int stepValue = 10;
private:
    int scrollBarHeight = 20;
    bool isPressScrollBar = false;
    Sprite *rangeSlider;
};

