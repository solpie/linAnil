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
#include "EventDispatcher.hpp"

/*
 * VsObj visible object
 * */
class VsObj : public EventDispatcher<VsObj> {
public:
    VsObj() {
        nvgContext = VS_CONTEXT;
    }

    ~VsObj() { }

    float width = 0;
    float height = 0;
    bool visible = true;
    //0~255
    float alpha = 255;
    float _x = 0;

    void setX(float x) { _x = x; }

    float x() {
        if (parent) {
            return parent->x() + _x;
        }
        return _x;
    }

    float _y = 0;

    void setY(float y) { _y = y; }

    float y() {
        if (parent) {
            return parent->y() + _y;
        }
        return _y;
    }

    virtual void render() { }

    virtual void aftRender() { }

    VsObj *parent = nullptr;
protected:
    NVGcontext *nvgContext = nullptr;
};