#pragma once
//
// Created by manoyuria on 2015/7/25.
//
#include "nanovg/nanovg.h"
#include "VsContext.hpp"

#define _3RGB(v) nvgRGB(v,v,v)
#define _3RGBA(v, a) nvgRGBA(v,v,v,a)
struct LineInfo {
    int x, y, width;
    NVGcolor nvgColor;
} _lineInfo;

void vsLineWidthColor(NVGcontext *vg, int width, NVGcolor col) {
    nvgFillColor(vg, col);

    _lineInfo.width = width;
    _lineInfo.nvgColor = col;
}

void vsMoveTo(NVGcontext *vg, int x, int y) {
    _lineInfo.x = x;
    _lineInfo.y = y;
}

void vsLineTo(NVGcontext *vg, int x, int y) {
    if (y == _lineInfo.y) {
        if (x > _lineInfo.x)
            nvgRect(vg, _lineInfo.x, _lineInfo.y, x - _lineInfo.x, _lineInfo.width);
        else if (x < _lineInfo.x)
            nvgRect(vg, x, y, _lineInfo.x - x + 1, _lineInfo.width);
    }
    else if (x == _lineInfo.x) {
        if (y > _lineInfo.y)
            nvgRect(vg, _lineInfo.x, _lineInfo.y, _lineInfo.width, y - _lineInfo.y);
        else if (y < _lineInfo.y)
            nvgRect(vg, x, y, _lineInfo.width, _lineInfo.y - y);

    }

    _lineInfo.x = x;
    _lineInfo.y = y;
}

//inner frame line
void vsLineRect(NVGcontext *vg, int x, int y, int width, int height) {
    vsMoveTo(vg, x, y);
    vsLineTo(vg, x + width - 1, y);
    vsLineTo(vg, x + width - 1, y + height - 1);
    vsLineTo(vg, x, y + height - 1);
    vsLineTo(vg, x, y);
}

void vsLine(NVGcontext *vg) {
    nvgFill(vg);
}

void vsDropShadow(NVGcontext *ctx, float x, float y, float w, float h,
                  float r, float feather, float alpha) {

    nvgBeginPath(ctx);
    y += feather;
    h -= feather;

    nvgMoveTo(ctx, x - feather, y - feather);
    nvgLineTo(ctx, x, y - feather);
    nvgLineTo(ctx, x, y + h - feather);
    nvgArcTo(ctx, x, y + h, x + r, y + h, r);
    nvgArcTo(ctx, x + w, y + h, x + w, y + h - r, r);
    nvgLineTo(ctx, x + w, y - feather);
    nvgLineTo(ctx, x + w + feather, y - feather);
    nvgLineTo(ctx, x + w + feather, y + h + feather);
    nvgLineTo(ctx, x - feather, y + h + feather);
    nvgClosePath(ctx);

    nvgFillPaint(ctx, nvgBoxGradient(ctx,
                                     x - feather * 0.5f, y - feather * 0.5f,
                                     w + feather, h + feather,
                                     r + feather * 0.5f,
                                     feather,
                                     nvgRGBAf(0, 0, 0, alpha * alpha),
                                     nvgRGBAf(0, 0, 0, 0)));
    nvgFill(ctx);
}
// stroke width of wire outline
#define BND_NODE_WIRE_OUTLINE_WIDTH 4
// stroke width of wire
#define BND_NODE_WIRE_WIDTH 2
#define BND_INLINE inline
#define bnd_fminf(a, b) fminf(a, b)
#define bnd_fmaxf(a, b) fmaxf(a, b)
#define bnd_fmin(a, b) fmin(a, b)
#define bnd_fmax(a, b) fmax(a, b)

void vsColoredNodeWire(NVGcontext *ctx, float x0, float y0, float x1, float y1,
                       NVGcolor color0, NVGcolor color1) {
    float length = bnd_fmaxf(fabsf(x1 - x0), fabsf(y1 - y0));
    // how much a noodle curves (0 to 10)
    int noodleCurving = 3;
    float delta = length * (float) noodleCurving / 10.0f;

    nvgBeginPath(ctx);
    nvgMoveTo(ctx, x0, y0);
    nvgBezierTo(ctx,
                x0 + delta, y0,
                x1 - delta, y1,
                x1, y1);
    NVGcolor colorw = nvgRGB(52, 22, 99);
    colorw.a = (color0.a < color1.a) ? color0.a : color1.a;
    nvgStrokeColor(ctx, colorw);
    nvgStrokeWidth(ctx, BND_NODE_WIRE_OUTLINE_WIDTH);
    nvgStroke(ctx);
    nvgStrokePaint(ctx, nvgLinearGradient(ctx,
                                          x0, y0, x1, y1,
                                          color0,
                                          color1));
    nvgStrokeWidth(ctx, BND_NODE_WIRE_WIDTH);
    nvgStroke(ctx);
}

#define fillRect(col, x, y, w, h) vg=VG_CONTEXT;\
nvgBeginPath(vg);\
nvgRect(vg, x, y, w, h);\
nvgFillColor(vg, col);\
nvgFill(vg);
