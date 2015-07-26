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
        add_event_on_context(MouseEvent::UP, onUp)
    }

    void onUp(void *e) {
        isPressScrollBar = false;
        isPressTimestamp = false;
    }

    void onDown(void *e) {
        cout << this << " mouseX: " << mouseX();
        if (mouseY() < scrollBarHeight) {
            isPressScrollBar = true;
            isPressTimestamp = false;
        }
        else {
            isPressScrollBar = false;
            isPressTimestamp = true;
            updateCursorPos();
        }

        _lastX = _lastY = 0;
    }

    void updateCursorPos() {
        int frameWidth = _proj->curCompInfo->frameWidth;
        _cursorFrame = (VS_CONTEXT.cursor.x - gX() + _value) / frameWidth;
        cout << typeid(this).name() << " cursor frame: " << _cursorFrame << endl;
    }

    virtual void onDraw() override {
        //bg
        fillRect(_3RGB(47), gX(), gY(), width, height);

        {//scroll bar
            float ratio = getContentWidth() / (width);
            _stepValue = ratio;
            float barWidth = width / ratio;
            int maxValue = (width - barWidth);

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
                    _value += dx;
                    limit(_value, 0, maxValue)
                    disEvent(VsEvent::CHANGED);
                    cout << this << " Width: " << width << endl;
                }
            }
            int barX = float(_value);
            nvgBeginPath(vg);
            nvgRect(vg, gX() + barX, gY(), barWidth, scrollBarHeight);
            nvgFillColor(vg, nvgRGB(88, 88, 88));
            nvgFill(vg);
        }
        int frameWidth = _proj->curCompInfo->frameWidth;

//        int cursorPx = gX() + _cursorFrame * frameWidth - _value;
        int cursorPx = gX() +_proj->curCompInfo->getCurrentFrame() * frameWidth - _value;
//        int cursorPx = gX() + _cursorPos - getValue();

        {//cursor
            if (isPressTimestamp)
                updateCursorPos();
            if (cursorPx > gX()) {
                //
                nvgBeginPath(vg);
                nvgRect(vg, cursorPx, gY() + height, frameWidth, _cursorFrameHeight);
                nvgFillColor(vg, _3RGBA(200, 128));
                nvgFill(vg);
            }

        }
        {//timestamp
            int fY = gY() + height - 10;
            int fCount = (getValue() / frameWidth);
            int sY = gY() + 30;
            char str[10];
            nvgScissor(vg, gX(), gY(), width, height);
            for (int fX = -(_value % frameWidth); fX < width; fX += frameWidth) {
                {//track name
                    nvgFontFace(vg, "sans");
                    nvgFontSize(vg, 14.0f);
                    nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
                    nvgFillColor(vg, nvgRGB(240, 240, 240));
                    sprintf(str, "%d", fCount++);
                    nvgText(vg, gX() + fX + 4, sY, str, nullptr);
//                    nvgTextBounds(vg, gX() + fX + 4, sY, str, nullptr);
//                    nvgSave(vg);
                }
                //tick line
                fillRect(_3RGB(20), gX() + fX, fY, 1, 10);
            }
        }
        {//cursor tri
            if (cursorPx > gX()) {
                nvgBeginPath(vg);
                nvgMoveTo(vg, cursorPx - 10, gY() + scrollBarHeight + 5);
                nvgLineTo(vg, cursorPx + 10, gY() + scrollBarHeight + 5);
                nvgLineTo(vg, cursorPx, gY() + scrollBarHeight + 15);
                nvgFillColor(vg, _3RGB(200));
                nvgFill(vg);
            }

        }

//        nvgSave(vg);

        VS_RENDER_CHILDREN();
    }

    void setSize(int w, int h) override {
        width = w;
        _cursorFrameHeight = h - height;
    }

    int getValue() {
        return _value * _stepValue;
    }

private:
    int _stepValue = 1;

    int getContentWidth() {
        //todo count when changed
        return _proj->curCompInfo->durationFrame * _proj->curCompInfo->frameWidth;
    }

    int _value = 0;
    int _lastX, _lastY;
    int _cursorFrameHeight = 300;
    int scrollBarHeight = 20;
    bool isPressScrollBar = false;
    bool isPressTimestamp = false;
    int _cursorFrame = 1;
};

