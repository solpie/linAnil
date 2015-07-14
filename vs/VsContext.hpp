#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_VSCONTEXT_HPP
#define LINANIL_VSCONTEXT_HPP

#endif //LINANIL_VSCONTEXT_HPP

#include <c++/4.9.2/exception>
#include <vs/events/VsEvent.hpp>
#include "nanovg/nanovg.h"
#include "VsObj.hpp"

#define VG_CONTEXT  VsContext::_().getContext()
#define VS_CONTEXT VsContext::_()
using namespace std;

#include "events/EventDispatcher.hpp"
#include "events/BaseEvent.hpp"

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
//        renderIdx = 0;
    }

    void endFrame() {
        popUIEvent();
    }

    void setMouseButton(unsigned int button, unsigned int mod, int act) {
        buttons = button;
        mods = mod;
        action = act;
        enabeld = 1;
        if (act == GLFW_PRESS)
            Evt_dis(VsEvent::STAGE_MOUSE_DOWN, nullptr)
        else if (act == GLFW_RELEASE)
            Evt_dis(VsEvent::STAGE_MOUSE_UP, nullptr)
    }

    void setCursor(int x, int y) {
        cursor.x = x;
        cursor.y = y;
    }

    pos cursor;

    void popUIEvent() {
        for (const auto &obs : _uiEvents) {
            BaseEvent *event = &obs.second;
            if (!event->isAccept) {
                ((EventDispatcher *) event->target)->disEvent(*event);
                event->isAccept = true;
            }
        }
        enabeld = 0;
    }


    void pushUIEvent(BaseEvent event) {
        _uiEvents[event.type] = event;
    }

protected:
    map<string, BaseEvent> _uiEvents;
    NVGcontext *nvgContext = nullptr;
};