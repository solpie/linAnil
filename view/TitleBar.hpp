//
// Created by toramisu on 2015/7/17.
//
#include "Sprite.hpp"

class TitleBar : public Sprite {
public:
    TitleBar() {
        height = 36;


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
        add_event_on(close, MouseEvent::UP, onClose)
        addChild(close);
        resize(VS_WIDTH, 0);
    }

    void onClose(void *e) {
        VS_CONTEXT.close();
    }

    void onDrawMinimize(void *e) {
        if (minimize->isHover) {
            nvgBeginPath(nvgContext);
            nvgRect(nvgContext, minimize->gX(), minimize->gY(), minimize->width, minimize->height);
            nvgFillColor(nvgContext, nvgRGB(58, 58, 58));
            nvgFill(nvgContext);
        }

        nvgBeginPath(nvgContext);
        nvgRect(nvgContext, minimize->gX() + 8, minimize->gY() + 15, 12, 2);
        if (minimize->isHover)
            nvgFillColor(nvgContext, nvgRGB(201, 201, 201));
        else
            nvgFillColor(nvgContext, nvgRGB(146, 146, 146));
        nvgFill(nvgContext);
    }

    void onDrawClose(void *e) {
        if (close->isHover) {
            nvgBeginPath(nvgContext);
            nvgRect(nvgContext, close->gX(), close->gY(), close->width, close->height);
            nvgFillColor(nvgContext, nvgRGB(190, 80, 80));
            nvgFill(nvgContext);
        }

//        nvgBeginPath(nvgContext);
//        nvgRect(nvgContext, minimize->gX() + 8, minimize->gY() + 15, 12, 2);
//        if (minimize->isHover)
//            nvgFillColor(nvgContext, nvgRGB(201, 201, 201));
//        else
//            nvgFillColor(nvgContext, nvgRGB(146, 146, 146));
//        nvgFill(nvgContext);
    }


    void onDrawMaximize(void *e) {
        if (maximize->isHover) {
            nvgBeginPath(nvgContext);
            nvgRect(nvgContext, maximize->gX(), maximize->gY(), maximize->width, maximize->height);
            nvgFillColor(nvgContext, nvgRGB(58, 58, 58));
            nvgFill(nvgContext);
        }

        nvgBeginPath(nvgContext);
        nvgRect(nvgContext, maximize->gX() + 8, maximize->gY() + 7, 12, 2);
        nvgRect(nvgContext, maximize->gX() + 8, maximize->gY() + 9, 1, 7);
        nvgRect(nvgContext, maximize->gX() + 8 + 11, maximize->gY() + 9, 1, 7);
        nvgRect(nvgContext, maximize->gX() + 8, maximize->gY() + 16, 12, 1);

        if (maximize->isHover)
            nvgFillColor(nvgContext, nvgRGB(201, 201, 201));
        else
            nvgFillColor(nvgContext, nvgRGB(146, 146, 146));


        nvgFill(nvgContext);

    }

    virtual void onDraw() override {
        nvgBeginPath(nvgContext);
        nvgRect(nvgContext, gX(), gY(), width, height);
        nvgFillColor(nvgContext, nvgRGB(22, 22, 22));
        nvgFill(nvgContext);

        nvgBeginPath(nvgContext);
        nvgRect(nvgContext, gX(), gY() + height - 3, width, 3);
        nvgFillColor(nvgContext, nvgRGB(250, 240, 20));
        nvgFill(nvgContext);

        VS_RENDER_CHILDREN();
    }

    void resize(int w, int h) {
        width = w;
        minimize->setX(w - 90);
        maximize->setX(w - 60);
        close->setX(w - 30);
    }

private:
    Sprite *minimize;
    Sprite *maximize;
    Sprite *close;
};

