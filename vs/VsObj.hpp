#pragma once
//
// Created by manoyuria on 2015/7/11.
//


#include "VsContext.hpp"
#include "events/EventDispatcher.hpp"
#include "VsGFX.hpp"
#include "CommonMethod.hpp"

/*
 * VsObj enable object
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
    VsObj *parent = nullptr;


    virtual void render() {
        updateZDepth();
    }
protected:
    int zdepth = -1;
    NVGcontext *vg = nullptr;
};