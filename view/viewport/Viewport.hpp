#include <view/tools/ColorWheel.hpp>
#include "Sprite.hpp"

#define VIEWPORT_WIDTH 1280
#define VIEWPORT_HEIGHT 720

class Viewport : public VsObjContainer {

public:
    Viewport() {
        char file[128];
//        snprintf(file, 128, "test/thumb/image1.jpg", i + 1);
        imagei = nvgCreateImage(VG_CONTEXT, "test/thumb/image1.jpg", 0);

        hSplitter = new Splitter(Direction::Horizontal);
        addChild(hSplitter);
        width = VIEWPORT_WIDTH;
        height = VIEWPORT_HEIGHT;
    }

    void render() override {
        fillRect(_3RGB(80), gX(), gY(), width, height);


        ImageInfo *imageInfo;
        TrackInfo *trkInfo;
        vector<TrackInfo *> *trkInfos = _proj->curCompInfo->getTrackInfos();
        for (int i = trkInfos->size() - 1; i > -1; --i) {
            trkInfo = (TrackInfo *) trkInfos->at(i);
            if (trkInfo->visible) {
                imageInfo = trkInfo->getCurrentImageInfo();
                if (imageInfo) {
                    nvgBeginPath(vg);
                    nvgRect(vg, gX(), gY(), imageInfo->width * scale, imageInfo->height * scale);
                    nvgFillPaint(vg,
                                 nvgImagePattern(vg, gX(), gY(), imageInfo->width * scale, imageInfo->height * scale, 0,
                                                 imageInfo->id, 1));
                    nvgFill(vg);
                }
            }
        }
        VS_RENDER_CHILDREN();
    }

    void rotation() {
        //        int w, h;
//        NVGpaint imgPaint;
//
//        nvgImageSize(vg, imagei, &w, &h);
//        imgPaint = nvgImagePattern(vg, gX() + 300, gY(), w * .5, h * .5, 0, imagei, 1);
//        nvgBeginPath(vg);
//        nvgRect(vg, gX() + 300, gY(), w * .5, h * .5);
//        nvgFillPaint(vg, imgPaint);
//        nvgFill(vg);
//
//        nvgBeginPath(vg);
//        float angle = 180.0f / 180.0f * NVG_PI;
//        int refH = h + 5;
////        nvgRotate(vg, angle);
//        nvgRect(vg, gX(), gY() + refH, w, h);
//        nvgFillPaint(vg, nvgImagePattern(vg, gX() + w, gY() + h + refH, w, h, NVG_PI, imagei, 1));
//        nvgFill(vg);

    }


    virtual void setSize(int w, int h) override;

private:
    Splitter *hSplitter;
    int imagei;
    Sprite *transport;
    float scale = 1;

};

void Viewport::setSize(int w, int h) {
    VsObj::setSize(w, h);
    float sx = float(w) / VIEWPORT_WIDTH;

    scale = float(h) / VIEWPORT_HEIGHT;
    if (scale > sx)
        scale = sx;
}
