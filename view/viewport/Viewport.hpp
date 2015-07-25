#include <view/tools/ColorWheel.hpp>
#include "Sprite.hpp"

class Viewport : public VsObjContainer {

public:
    Viewport() {
        height = 720;
        char file[128];
//        snprintf(file, 128, "test/thumb/image1.jpg", i + 1);
        imagei = nvgCreateImage(VG_CONTEXT, "test/thumb/image1.jpg", 0);
        ColorWheel *colorWheel = new ColorWheel;
        colorWheel->move(300, 300);
        colorWheel->setSize(300, 300);
        addChild(colorWheel);
//        imagei = nvgCreateImage(VG_CONTEXT, "test/test10/image001.png", 0);
    }

    void render() override {
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, _3RGB(80));
        nvgFill(vg);

        int w, h;
        NVGpaint imgPaint;

        nvgImageSize(vg, imagei, &w, &h);
        imgPaint = nvgImagePattern(vg, gX()+300, gY(), w*.5, h*.5, 0, imagei, 1);
        nvgBeginPath(vg);
        nvgRect(vg, gX()+300, gY(), w*.5, h*.5);
        nvgFillPaint(vg, imgPaint);
        nvgFill(vg);

        nvgBeginPath(vg);
        float angle = 180.0f/180.0f*NVG_PI;
        int refH = h+5;
//        nvgRotate(vg, angle);
        nvgRect(vg, gX(), gY()+refH, w, h);
        nvgFillPaint(vg, nvgImagePattern(vg, gX()+w, gY()+h+refH, w, h, NVG_PI, imagei, 1));
        nvgFill(vg);

        VS_RENDER_CHILDREN();
    }

    void resize(int w, int h) {
        width = w;
//        height = h;
    }

private:
//    ColorWheel *colorWheel;
    int imagei;
    Sprite *transport;
};