//
// Created by toramisu on 2015/7/17.
//
#include "Sprite.hpp"

class TitleBar : public Sprite {
public:
    TitleBar() {
        height = 36;
        add_event(MouseEvent::DOWN, onDown)
        add_event(MouseEvent::UP, onUp)
//        add_event_on_context(VsEvent::STAGE_MOUSE_UP,onUp)



        minimize = new Sprite();
        minimize->setSize(29, 25);
        minimize->isInteractive = true;
        add_event_on(minimize, SpriteEvent::DRAW, onDrawMinimize)
        addChild(minimize);

        maximize = new Sprite();
        maximize->setSize(29, 25);
        maximize->isInteractive = true;
        add_event_on(maximize, SpriteEvent::DRAW, onDrawMaximize)
        addChild(maximize);

        close = new Sprite();
        close->setSize(29, 25);
        close->isInteractive = true;
        add_event_on(close, SpriteEvent::DRAW, onDrawClose)
        addChild(close);

        add_event_on(minimize, MouseEvent::UP, onMinimize)
        add_event_on(maximize, MouseEvent::UP, onMaximize)
        add_event_on(close, MouseEvent::UP, onClose)
        resize(VS_WIDTH, 0);


    }

    void onDown(void *e) {
        _isPress = true;
        _lastX = _lastY = 0;
    }


    void onMove() {
        if (_isPress&&!VS_CONTEXT.isMaximized) {
            POINT mpos;
            GetCursorPos(&mpos);
            int dx = 0, dy = 0;
            if (_lastX)
                dx = mpos.x - _lastX;
            _lastX = mpos.x;

            if (_lastY)
                dy = mpos.y - _lastY;
            _lastY = mpos.y;
            if (dx != 0 || dy != 0) {
                VS_CONTEXT.moveWindow(dx, dy);
            }
        }
    }

    void onUp(void *e) {
        _isPress = false;
    }

    void onMinimize(void *e) {
        VS_CONTEXT.minimize();
    }

    void onMaximize(void *e) {
        VS_CONTEXT.maximize();
    }

    void onClose(void *e) {
        VS_CONTEXT.close();
    }

    void onDrawMinimize(void *e) {
        if (minimize->isHover) {
            nvgBeginPath(vg);
            nvgRect(vg, minimize->gX(), minimize->gY(), minimize->width, minimize->height);
            nvgFillColor(vg, nvgRGB(58, 58, 58));
            nvgFill(vg);
        }

        nvgBeginPath(vg);
        nvgRect(vg, minimize->gX() + 8, minimize->gY() + 15, 12, 2);
        if (minimize->isHover)
            nvgFillColor(vg, nvgRGB(201, 201, 201));
        else
            nvgFillColor(vg, nvgRGB(146, 146, 146));
        nvgFill(vg);
    }

    void onDrawClose(void *e) {
        if (close->isHover) {
            nvgBeginPath(vg);
            nvgRect(vg, close->gX(), close->gY(), close->width, close->height);
            nvgFillColor(vg, nvgRGB(190, 80, 80));
            nvgFill(vg);
        }

//        nvgBeginPath(vg);
//        nvgRect(vg, minimize->gX() + 8, minimize->gY() + 15, 12, 2);
//        if (minimize->isHover)
//            nvgFillColor(vg, nvgRGB(201, 201, 201));
//        else
//            nvgFillColor(vg, nvgRGB(146, 146, 146));
//        nvgFill(vg);
    }


    void onDrawMaximize(void *e) {
        if (maximize->isHover) {
            nvgBeginPath(vg);
            nvgRect(vg, maximize->gX(), maximize->gY(), maximize->width, maximize->height);
            nvgFillColor(vg, nvgRGB(58, 58, 58));
            nvgFill(vg);
        }

        nvgBeginPath(vg);
        nvgRect(vg, maximize->gX() + 8, maximize->gY() + 7, 12, 2);
        nvgRect(vg, maximize->gX() + 8, maximize->gY() + 9, 1, 7);
        nvgRect(vg, maximize->gX() + 8 + 11, maximize->gY() + 9, 1, 7);
        nvgRect(vg, maximize->gX() + 8, maximize->gY() + 16, 12, 1);

        if (maximize->isHover)
            nvgFillColor(vg, nvgRGB(201, 201, 201));
        else
            nvgFillColor(vg, nvgRGB(146, 146, 146));


        nvgFill(vg);

    }

    virtual void onDraw() override {
        onMove();
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, nvgRGB(22, 22, 22));
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY() + height - 3, width, 3);
        nvgFillColor(vg, nvgRGB(250, 240, 20));
        nvgFill(vg);

        VS_RENDER_CHILDREN();
    }

    void resize(int w, int h) {
        width = w;
        minimize->setX(w - 90);
        maximize->setX(w - 60);
        close->setX(w - 30);
    }

private:
    bool _isPress = false;
    int _lastX = 0, _lastY = 0;
    Sprite *minimize;
    Sprite *maximize;
    Sprite *close;
};

