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
        add_event_on_context(VsEvent::STAGE_MOUSE_UP, onUp)
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

        _lastX = _lastY = 0;
    }

    virtual void onDraw() override {
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, nvgRGB(47, 47, 47));
        nvgFill(vg);

        //scroll bar
        {

            float raito = contentWidth / (width);
            float barWidth = width / raito;
            int maxValue = float(width - barWidth) * stepValue;

            if (isPressScrollBar) {
                pos mpos = VS_CONTEXT.cursor;
                int dx = 0, dy = 0;
                if (_lastX)
                    dx = mpos.x - _lastX;
                _lastX = mpos.x;

                if (_lastY)
                    dy = mpos.y - _lastY;
                _lastY = mpos.y;
                if (dx != 0 || dy != 0) {
                    _value += dx * stepValue;
                    limit(_value, 0, maxValue)
                    cout << this << " Width: " << width << endl;
                }
            }
            int barX = float(_value) / stepValue;
            nvgBeginPath(vg);
            nvgRect(vg, gX() + barX, gY(), barWidth, scrollBarHeight);
            nvgFillColor(vg, nvgRGB(88, 88, 88));
            nvgFill(vg);
        }


        VS_RENDER_CHILDREN();
    }

    void resize(int w, int h) {
        width = w;
    }

    int getValue() {
        return _value * stepValue;
    }

    int contentWidth = 1440 * 3;
    int stepValue = 10;
private:
    int _value = 0;
    int _lastX, _lastY;
    int scrollBarHeight = 20;
    bool isPressScrollBar = false;
    Sprite *rangeSlider;
};

