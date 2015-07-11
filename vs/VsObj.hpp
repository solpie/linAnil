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

/*
 * VsObj visible object
 * */
class VsObj {
public:
    VsObj() {
        nvgContext = VS_CONTEXT;
    }

    ~VsObj() { }

    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
    bool visible = true;
    virtual void render() { }

protected:
    NVGcontext *nvgContext = nullptr;
};