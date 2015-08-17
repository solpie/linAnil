#pragma once

#include <view/tools/ColorWheel.hpp>
#include "Sprite.hpp"
#include "model/App.hpp"

#define VIEWPORT_WIDTH 1280
#define VIEWPORT_HEIGHT 720


class Viewport : public VsObjContainer {

public:
    Viewport() {
//        char file[128];
//        snprintf(file, 128, "test/thumb/image1.jpg", i + 1);
//        imagei = nvgCreateImage(VG_CONTEXT, "test/thumb/image1.jpg", 0);

        hSplitter = new Splitter(Direction::Horizontal);
        addChild(hSplitter);
        width = VIEWPORT_WIDTH;
        height = VIEWPORT_HEIGHT;
    }

    void render() override {
        //bg
//        fillRect(_3RGB(80), gX(), gY(), width, height);

        ImageInfo *imageInfo;
        BaseTrackInfo *trkInfob;
        TrackInfo *trkInfo;
        vector<BaseTrackInfo *> *trkInfos = _proj->curCompInfo->getTrackInfos();
        for (int i = trkInfos->size() - 1; i > -1; --i) {
            trkInfob = trkInfos->at(i);
            if (trkInfob->type == TrackType::Image) {
                trkInfo = (TrackInfo *) trkInfob;
                if (trkInfo->enable) {
                    imageInfo = trkInfo->getCurrentImageInfo();
                    if (imageInfo) {
                        nvgBeginPath(vg);
                        nvgRect(vg, gX(), gY(), imageInfo->width * scale, imageInfo->height * scale);
//                        nvgFillPaint(vg,
//                                     nvgImagePattern(vg, gX(), gY(), imageInfo->thumbW * scale,
//                                                     imageInfo->thumbH * scale, 0,
//                                                     imageInfo->thumbId, trkInfo->getOpacity()));
                        nvgFillPaint(vg,
                                     nvgImagePattern(vg, gX(), gY(), imageInfo->width * scale,
                                                     imageInfo->height * scale, 0,
                                                     imageInfo->id, trkInfo->getOpacity()));
                        nvgFill(vg);
                    }
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
//    int imagei;
    Sprite *transport;
    float scale = 1;
};

void Viewport::setSize(int w, int h) {
    VsObj::setSize(w, h);
    float sx = float(w) / VIEWPORT_WIDTH;

    if (_conf->viewport.scaleMode == ScaleMode::Fit) {
        scale = float(h) / VIEWPORT_HEIGHT;
        if (scale > sx)
            scale = sx;
    }
    else if (_conf->viewport.scaleMode == ScaleMode::None)
        scale = 1;
}
