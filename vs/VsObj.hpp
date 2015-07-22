#pragma once
//
// Created by manoyuria on 2015/7/11.
//
#pragma once
#ifndef KIUITEST_DISPLAYOBJ_HPP
#define KIUITEST_DISPLAYOBJ_HPP

#endif //KIUITEST_DISPLAYOBJ_HPP

#include "nanovg/nanovg.h"
#include "VsContext.hpp"
#include "events/EventDispatcher.hpp"

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
            nvgRect(vg, x, y, _lineInfo.x - x, _lineInfo.width);
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

void vsLineRect(NVGcontext *vg, int x, int y, int width, int height) {
    vsMoveTo(vg, x, y);
    vsLineTo(vg, x + width, y);
    vsLineTo(vg, x + width, y + height);
    vsLineTo(vg, x, y + height);
    vsLineTo(vg, x, y);
}

/*
 * VsObj visible object
 * */
class VsObj : public EventDispatcher {
public:
    VsObj() {
        vg = VG_CONTEXT;
    }

    ~VsObj() { }

    int width = 0;
    int height = 0;
    bool visible = true;
    //0~255
    int alpha = 255;

    int _x = 0;

    void setX(int x) { _x = x; }

    int x() { return _x; }

    //todo set gX() when parent changed
    int gX() {
        if (parent)
            return parent->gX() + _x;
        return _x;
    }

    int _y = 0;

    int y() { return _y; }

    void setY(int y) { _y = y; }

    int gY() {
        if (parent)
            return parent->gY() + _y;
        return _y;
    }

    void move(int x, int y) {
        _x = x;
        _y = y;
    }

    void updateZDepth() {
//        zdepth = VS_CONTEXT.renderIdx++;
    }

    virtual void setSize(int w, int h) {
        if (w > -1)
            width = w;
        if (h > -1)
            height = h;
    }

    virtual void render() {
        updateZDepth();
    }

    VsObj *parent = nullptr;
    int zdepth = -1;
protected:
    NVGcontext *vg = nullptr;
};