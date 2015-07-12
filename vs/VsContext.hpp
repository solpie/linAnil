#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_VSCONTEXT_HPP
#define LINANIL_VSCONTEXT_HPP

#endif //LINANIL_VSCONTEXT_HPP

#include <c++/4.9.2/exception>
#include "nanovg/nanovg.h"
#include "EventDispatcher.hpp"
#include "VsObj.hpp"

#define VG_CONTEXT  VsContext::_().getContext()
#define VS_CONTEXT VsContext::_()
using namespace std;

template<typename T>
class S {
public:
    static T &_() {
        static T instance;
        return instance;
    }
};

struct pos {
    int x;
    int y;
};

class VsContext : public S<VsContext> {
public:
    NVGcontext *init() {

        //_vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        nvgContext = nvgCreateGL3(NVG_ANTIALIAS);
        return nvgContext;
    }

    NVGcontext *getContext() {
        if (nvgContext)
            return nvgContext;
        else {
            string e = "call init() first!";
            cout << this << e << endl;
            throw runtime_error(e.c_str());
        }
    }

    unsigned int buttons;
    int mods;
    int enabeld;
    int action;
    void *top = nullptr;
    int renderIdx;

    void beginFrame() {
        renderIdx = 0;
    }

    void endFrame() {
//        cout << "endFrame" << VS_CONTEXT.top << endl;
//        VS_CONTEXT.top = nullptr;
//        top->disEvent();
        popUIEvent();
    }

    void setMouseButton(unsigned int button, unsigned int mod, int act) {
        buttons = button;
        mods = mod;
        action = act;
        enabeld = 1;
    }

    void setCursor(int x, int y) {
        cursor.x = x;
        cursor.y = y;
    }

    pos cursor;

    void popUIEvent() {
        int count = _uiEvents.size();
        for (const auto &obs : _uiEvents) {
            obs.second();
        }
        _uiEvents.clear();
        count = _uiEvents.size();

        enabeld = 0;
    }

    template<typename Observer>
    void push(const string &event, Observer &&observer) {
        _uiEvents[event] = forward<function<void()>>(observer);
    }

protected:
    map<string, function<void()>> _uiEvents;

    NVGcontext *nvgContext = nullptr;
};