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

#define _nvgcontext nvgContext


/*
 * VsObj visible object
 * */
class VsObj : public EventDispatcher {
public:
    VsObj() {
        vg = VG_CONTEXT;
    }

    ~VsObj() { }

    float width = 0;
    float height = 0;
    bool visible = true;
    //0~255
    float alpha = 255;

    float _x = 0;

    void setX(float x) { _x = x; }

    float x() { return _x; }

    float gX() {
        if (parent)
            return parent->gX() + _x;
        return _x;
    }

    float _y = 0;

    float y() { return _y; }

    void setY(float y) { _y = y; }

    float gY() {
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

    virtual void render() {
        updateZDepth();
    }

    VsObj *parent = nullptr;
    int zdepth = -1;
protected:
    NVGcontext *vg = nullptr;
};