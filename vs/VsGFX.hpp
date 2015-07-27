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
            nvgRect(vg, x, y, _lineInfo.x - x+1, _lineInfo.width);
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
    vsLineTo(vg, x + width-1, y);
    vsLineTo(vg, x + width-1, y + height-1);
    vsLineTo(vg, x, y + height-1);
    vsLineTo(vg, x, y);
}

void vsLine(NVGcontext *vg) {
    nvgFill(vg);
}

#define fillRect(col, x, y, w, h) vg=VG_CONTEXT;\
nvgBeginPath(vg);\
nvgRect(vg, x, y, w, h);\
nvgFillColor(vg, col);\
nvgFill(vg);
