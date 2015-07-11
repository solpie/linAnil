#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_TRACKAREA_HPP
#define LINANIL_TRACKAREA_HPP

#endif //LINANIL_TRACKAREA_HPP

#include "vs/VsObjContainer.hpp"
#include "math.h"

class TrackArea : public VsObjContainer {

};

static float maxf(float a, float b) { return a > b ? a : b; }

static float clampf(float a, float mn, float mx) { return a < mn ? mn : (a > mx ? mx : a); }

void drawSpinner(NVGcontext *vg, float cx, float cy, float r, float t) {
    float a0 = 0.0f + t * 6;
    float a1 = NVG_PI + t * 6;
    float r0 = r;
    float r1 = r * 0.75f;
    float ax, ay, bx, by;
    NVGpaint paint;

    nvgSave(vg);

    nvgBeginPath(vg);
    nvgArc(vg, cx, cy, r0, a0, a1, NVG_CW);
    nvgArc(vg, cx, cy, r1, a1, a0, NVG_CCW);
    nvgClosePath(vg);
    ax = cx + cosf(a0) * (r0 + r1) * 0.5f;
    ay = cy + sinf(a0) * (r0 + r1) * 0.5f;
    bx = cx + cosf(a1) * (r0 + r1) * 0.5f;
    by = cy + sinf(a1) * (r0 + r1) * 0.5f;
    paint = nvgLinearGradient(vg, ax, ay, bx, by, nvgRGBA(0, 0, 0, 0), nvgRGBA(0, 0, 0, 128));
    nvgFillPaint(vg, paint);
    nvgFill(vg);

    nvgRestore(vg);
}

void drawThumbnails(NVGcontext *vg, float x, float y, float w, float h, const int *images, int nimages, float t) {
    float cornerRadius = 3.0f;
    NVGpaint shadowPaint, imgPaint, fadePaint;
    float ix, iy, iw, ih;
    float thumb = 60.0f;
    float arry = 30.5f;
    int imgw, imgh;
    float stackh = (nimages / 2) * (thumb + 10) + 10;
    int i;
    float u = (1 + cosf(t * 0.5f)) * 0.5f;
    float u2 = (1 - cosf(t * 0.2f)) * 0.5f;
    float scrollh, dv;

    nvgSave(vg);
//	nvgClearState(vg);

    // Drop shadow
    shadowPaint = nvgBoxGradient(vg, x, y + 4, w, h, cornerRadius * 2, 20, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
    nvgBeginPath(vg);
    nvgRect(vg, x - 10, y - 10, w + 20, h + 30);
    nvgRoundedRect(vg, x, y, w, h, cornerRadius);
    nvgPathWinding(vg, NVG_HOLE);
    nvgFillPaint(vg, shadowPaint);
    nvgFill(vg);

    // Window
    nvgBeginPath(vg);
    nvgRoundedRect(vg, x, y, w, h, cornerRadius);
    nvgMoveTo(vg, x - 10, y + arry);
    nvgLineTo(vg, x + 1, y + arry - 11);
    nvgLineTo(vg, x + 1, y + arry + 11);
    nvgFillColor(vg, nvgRGBA(200, 200, 200, 255));
    nvgFill(vg);

    nvgSave(vg);
    nvgScissor(vg, x, y, w, h);
    nvgTranslate(vg, 0, -(stackh - h) * u);

    dv = 1.0f / (float) (nimages - 1);

    for (i = 0; i < nimages; i++) {
        float tx, ty, v, a;
        tx = x + 10;
        ty = y + 10;
        tx += (i % 2) * (thumb + 10);
        ty += (i / 2) * (thumb + 10);
        nvgImageSize(vg, images[i], &imgw, &imgh);
        if (imgw < imgh) {
            iw = thumb;
            ih = iw * (float) imgh / (float) imgw;
            ix = 0;
            iy = -(ih - thumb) * 0.5f;
        } else {
            ih = thumb;
            iw = ih * (float) imgw / (float) imgh;
            ix = -(iw - thumb) * 0.5f;
            iy = 0;
        }

        v = i * dv;
        a = clampf((u2 - v) / dv, 0, 1);

        if (a < 1.0f)
            drawSpinner(vg, tx + thumb / 2, ty + thumb / 2, thumb * 0.25f, t);

        imgPaint = nvgImagePattern(vg, tx + ix, ty + iy, iw, ih, 0.0f / 180.0f * NVG_PI, images[i], a);
        nvgBeginPath(vg);
        nvgRoundedRect(vg, tx, ty, thumb, thumb, 5);
        nvgFillPaint(vg, imgPaint);
        nvgFill(vg);

        shadowPaint = nvgBoxGradient(vg, tx - 1, ty, thumb + 2, thumb + 2, 5, 3, nvgRGBA(0, 0, 0, 128),
                                     nvgRGBA(0, 0, 0, 0));
        nvgBeginPath(vg);
        nvgRect(vg, tx - 5, ty - 5, thumb + 10, thumb + 10);
        nvgRoundedRect(vg, tx, ty, thumb, thumb, 6);
        nvgPathWinding(vg, NVG_HOLE);
        nvgFillPaint(vg, shadowPaint);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgRoundedRect(vg, tx + 0.5f, ty + 0.5f, thumb - 1, thumb - 1, 4 - 0.5f);
        nvgStrokeWidth(vg, 1.0f);
        nvgStrokeColor(vg, nvgRGBA(255, 255, 255, 192));
        nvgStroke(vg);
    }
    nvgRestore(vg);

    // Hide fades
    fadePaint = nvgLinearGradient(vg, x, y, x, y + 6, nvgRGBA(200, 200, 200, 255), nvgRGBA(200, 200, 200, 0));
    nvgBeginPath(vg);
    nvgRect(vg, x + 4, y, w - 8, 6);
    nvgFillPaint(vg, fadePaint);
    nvgFill(vg);

    fadePaint = nvgLinearGradient(vg, x, y + h, x, y + h - 6, nvgRGBA(200, 200, 200, 255), nvgRGBA(200, 200, 200, 0));
    nvgBeginPath(vg);
    nvgRect(vg, x + 4, y + h - 6, w - 8, 6);
    nvgFillPaint(vg, fadePaint);
    nvgFill(vg);

    // Scroll bar
    shadowPaint = nvgBoxGradient(vg, x + w - 12 + 1, y + 4 + 1, 8, h - 8, 3, 4, nvgRGBA(0, 0, 0, 32),
                                 nvgRGBA(0, 0, 0, 92));
    nvgBeginPath(vg);
    nvgRoundedRect(vg, x + w - 12, y + 4, 8, h - 8, 3);
    nvgFillPaint(vg, shadowPaint);
//	nvgFillColor(vg, nvgRGBA(255,0,0,128));
    nvgFill(vg);

    scrollh = (h / stackh) * (h - 8);
    shadowPaint = nvgBoxGradient(vg, x + w - 12 - 1, y + 4 + (h - 8 - scrollh) * u - 1, 8, scrollh, 3, 4,
                                 nvgRGBA(220, 220, 220, 255), nvgRGBA(128, 128, 128, 255));
    nvgBeginPath(vg);
    nvgRoundedRect(vg, x + w - 12 + 1, y + 4 + 1 + (h - 8 - scrollh) * u, 8 - 2, scrollh - 2, 2);
    nvgFillPaint(vg, shadowPaint);
//	nvgFillColor(vg, nvgRGBA(0,0,0,128));
    nvgFill(vg);

    nvgRestore(vg);
}