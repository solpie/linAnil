//
// Created by toramisu on 2015/7/17.
//
#include "Sprite.hpp"
#include "menu/PopupMenu.hpp"
#include "menu/PopupMenuInfo.hpp"

enum TimestampType {
    Frame,
    Sec
};

class TimestampBar : public Sprite {
public:
    TimestampBar() {
        height = 35;
        //menu
        _settingMenu = new PopupMenuInfo("Timestamp setting");
        _settingMenu->width = 220;
        _settingMenu->addMenuItem("show in frame", [this](void *e) {
            _timestampType = TimestampType::Frame;
        });
        _settingMenu->addMenuItem("show in sec", [this](void *e) {
            _timestampType = TimestampType::Sec;
        });
        add_event(MouseEvent::DOWN, onDown);
        add_event(MouseEvent::UP, onUp);
        add_event(MouseEvent::RIGHT_UP, onRightUp);
        add_event_on_context(MouseEvent::UP, onUp)

        colLeft = nvgRGBA(255, 255, 255, 128);
        colRight = nvgRGBA(255, 255, 255, 10);
    }

    void onRightUp(void *e) {
        _popupMenu.show(_settingMenu->title(), _settingMenu->getMenuItems(),_settingMenu->width);
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
        int cursorFrame = (VS_CONTEXT.cursor.x - gX() + getValue()) / frameWidth;
        _proj->curCompInfo->setCurrentFrame(cursorFrame);
        cout << typeid(this).name() << " cursor frame: " << cursorFrame << endl;
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






//            nvgBeginPath(vg);
//            nvgRoundedRect(vg, gX() + barX, gY() + 2, barWidth, scrollBarHeight, 5);
//            nvgStrokeColor(vg, _3RGB(20));
//            nvgStrokeWidth(vg, 1);
//            nvgStroke(vg);
//            nvgFillPaint(vg, nvgLinearGradient(vg, gX() + barX, gY()+2, gX() + barX, gY() + scrollBarHeight,
//                                               _3RGB(76), _3RGB(64)));
//            nvgFill(vg);

            int gBarX = gX() + barX;

            nvgBeginPath(vg);
            vsLineWidthColor(vg, 1, _3RGB(30));
            vsLineRect(vg, gBarX, gY(), barWidth, scrollBarHeight);
            vsLine(vg);


            nvgBeginPath(vg);
            vsLineWidthColor(vg, 1, _3RGB(90));
            vsLineRect(vg, gBarX + 1, gY() + 1, barWidth - 2, scrollBarHeight - 2);
            vsLine(vg);
            fillRect(_3RGB(80), gBarX + 2, gY() + 2, barWidth - 4, scrollBarHeight - 4)

            if (isMouseInRect(gBarX, gY(), barWidth, scrollBarHeight)) {
                fillRect(_3RGB(100), gBarX + 4, gY() + 4, 2, 6)
                fillRect(_3RGB(100), gBarX + barWidth - 6, gY() + 4, 2, 6)
            }

//            fillRect(_3RGB(20), gX() + barX + 5, gY()+1, barWidth - 10, 1)
//            fillRect(_3RGB(88), gX() + barX + 4, gY()+1, barWidth - 8, 1)
        }
        int scrollValue = getValue();

        int frameWidth = _proj->curCompInfo->frameWidth;

//        int cursorPx = gX() + _cursorFrame * frameWidth - _value;
        int cursorPx = gX() + _proj->curCompInfo->getCurrentFrame() * frameWidth - scrollValue;
//        int cursorPx = gX() + _cursorPos - getValue();

        {//cursor
            if (isPressTimestamp)
                updateCursorPos();
            if (cursorPx > gX()) {
                //
                nvgBeginPath(vg);
                nvgRect(vg, cursorPx, gY() + height, frameWidth, _cursorFrameHeight);
                nvgFillPaint(vg, nvgLinearGradient(vg, cursorPx + frameWidth - 10, gY() + height, cursorPx + frameWidth,
                                                   gY() + height,
                                                   colRight, colLeft));
                nvgFill(vg);
                nvgBeginPath(vg);
                nvgRect(vg, cursorPx, gY() + height, frameWidth, _cursorFrameHeight);
                nvgFillPaint(vg, nvgLinearGradient(vg, cursorPx, gY() + height, cursorPx + 10, gY() + height,
                                                   colLeft, colRight));
                nvgFill(vg);

                fillRect(nvgRGB(THEME_COLOR_TITLEBAR_BOTTOM_BORDER), cursorPx, gY() + height - 18, frameWidth, 3)
            }

        }
        //border
        int borderTop = gY() + height - 20;
        fillRect(nvgRGB(THEME_COLOR_PANEL_BORDER_DARK), gX(), borderTop, width, 1)
        fillRect(nvgRGB(THEME_COL_PANEL_BORDER_LIGHT), gX(), borderTop + 1, width, 1)

        if (_timestampType == TimestampType::Frame) {//timestamp
            int fY = gY() + height - 10;
            int fCount = scrollValue / frameWidth;
            int sY = gY() + 20;
            char str[10];
            nvgScissor(vg, gX(), gY(), width, height);
            for (int fX = -(scrollValue % frameWidth); fX < width; fX += frameWidth) {
                //track name
                nvgFontFace(vg, "sans");
                nvgFontSize(vg, 14.0f);
                nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
                nvgFillColor(vg, nvgRGB(240, 240, 240));
                sprintf(str, "%d", fCount++);
                nvgText(vg, gX() + fX + 4, sY, str, nullptr);
//                    nvgTextBounds(vg, gX() + fX + 4, sY, str, nullptr);
//                    nvgSave(vg);
                //tick line
                fillRect(_3RGB(20), gX() + fX, fY, 1, 10);
            }
        }
        //cursor tri
//        if (cursorPx > gX()) {
//            nvgBeginPath(vg);
//            nvgMoveTo(vg, cursorPx - 10, gY() + scrollBarHeight + 5);
//            nvgLineTo(vg, cursorPx + 10, gY() + scrollBarHeight + 5);
//            nvgLineTo(vg, cursorPx, gY() + scrollBarHeight + 15);
//            nvgFillColor(vg, _3RGB(200));
//            nvgFill(vg);
//        }
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

    int _timestampType = TimestampType::Frame;
    PopupMenuInfo *_settingMenu;
    NVGcolor colLeft;
    NVGcolor colRight;
    int _value = 0;
    int _lastX, _lastY;
    int _cursorFrameHeight = 300;
    int scrollBarHeight = 15;
    bool isPressScrollBar = false;
    bool isPressTimestamp = false;
};

