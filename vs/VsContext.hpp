#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_VSCONTEXT_HPP
#define LINANIL_VSCONTEXT_HPP

#endif //LINANIL_VSCONTEXT_HPP

#include <stdio.h>

#ifdef NANOVG_GLEW

#include <GL/glew.h>

#endif
#ifdef __APPLE__
#	define GLFW_INCLUDE_GLCOREARB
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include "nanovg/nanovg.h"

#define NANOVG_GL3_IMPLEMENTATION

#include "nanovg/nanovg_gl.h"
#include <exception>
#include <vs/events/VsEvent.hpp>
#include "VsObj.hpp"

#define VG_CONTEXT  VsContext::_().getContext()
#define VS_CONTEXT VsContext::_()
#define add_event_on_context(type, func) VS_CONTEXT.add_event(type,func);

#include "events/EventDispatcher.hpp"
#include "events/BaseEvent.hpp"
#include "Performance.hpp"

#define VS_WIDTH 1440
#define VS_HEIGHT 920
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

void errorcb(int error, const char *desc) {
    cout << "GLFW error " << error << ": " << desc << endl;
}

void mousebutton(GLFWwindow *window, int button, int action, int mods);

void cursorpos(GLFWwindow *window, double x, double y);

void scrollevent(GLFWwindow *window, double x, double y) {
    NVG_NOTUSED(window);
//    uiSetScroll((int) x, (int) y);
}

void charevent(GLFWwindow *window, unsigned int value) {
    NVG_NOTUSED(window);
//    uiSetChar(value);
}

void key(GLFWwindow *window, int key, int scancode, int action, int mods) {
    NVG_NOTUSED(scancode);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
//    uiSetKey(key, mods, action);
}

class VsContext : public EventDispatcher, public S<VsContext> {
public:
    Performance *perfFps;
    Performance *perfCpu;
    GLFWwindow *window;

    void initVsContext() {
        nvgContext = nvgCreateGL3(NVG_ANTIALIAS);
        nvgCreateFont(nvgContext, "icons", "fonts/entypo.ttf");
        nvgCreateFont(nvgContext, "sans", "fonts/Roboto-Regular.ttf");
        nvgCreateFont(nvgContext, "sans-bold", "fonts/Roboto-Bold.ttf");
        nvgCreateFont(nvgContext, "system", "oui/DejaVuSans.ttf");
        nvgCreateImage(nvgContext, "oui/blender_icons16.png", 0);

        perfFps = new Performance(nvgContext);
        perfFps->setX(5);
        perfFps->setY(5);
        perfFps->initGraph(GRAPH_RENDER_FPS, "Frame Time");
//        addChild(perfFps);

        perfCpu = new Performance(nvgContext);
        perfCpu->setX(perfFps->gX() + perfFps->width + 5);
        perfCpu->setY(5);
        perfCpu->initGraph(GRAPH_RENDER_MS, "CPU Time");
        disEvent(VsEvent::INITED);
    }

    void run() {

        if (!glfwInit()) {
            printf("Failed to init GLFW.");
//            return -1;
        }
//        glfwSetErrorCallback([this](int error, const char *desc) { this->errorcb(error, desc); });
        glfwSetErrorCallback(errorcb);

//#ifndef _WIN32 // don't require this on win32, and works with more cards
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#endif
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
        //no title bar no border
        glfwWindowHint(GLFW_DECORATED, false);

        window = glfwCreateWindow(VS_WIDTH, VS_HEIGHT, "", nullptr, nullptr);
        if (!window) {
            glfwTerminate();
//            return -1;
        }
        glfwSetKeyCallback(window, key);
        glfwSetCharCallback(window, charevent);
        glfwSetCursorPosCallback(window, cursorpos);
        glfwSetMouseButtonCallback(window, mousebutton);
        glfwSetScrollCallback(window, scrollevent);

        glfwMakeContextCurrent(window);
#ifdef NANOVG_GLEW
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            cout << "Could not init glew." << endl;
//            return -1;
        }
        // GLEW generates GL error because it calls glGetString(GL_EXTENSIONS), we'll consume it here.
        glGetError();
#endif
        ////////////////////////vg

//        _vg = VsContext::_().init();
//        if (_vg == NULL) {
//            printf("Could not init nanovg.\n");
//            return -1;
//        }
        initVsContext();
//        init(_vg);
        //limit fps to monitor on=1 off=0
        glfwSwapInterval(1);

        glfwSetTime(0);

        double c = 0.0;
        int total = 0;
        bool isPerf = true;
//        if (isPerf) {
        double prevt = 0, cpuTime = 0;
//        }

        while (!glfwWindowShouldClose(window)) {
            double mx, my;
            int winWidth, winHeight;
            int fbWidth, fbHeight;
            float pxRatio;

            double t, dt;
            if (isPerf) {
                t = glfwGetTime();
                dt = t - prevt;
                prevt = t;
            }


            glfwGetCursorPos(window, &mx, &my);
            glfwGetWindowSize(window, &winWidth, &winHeight);
            glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
            // Calculate pixel ration for hi-dpi devices.
            pxRatio = (float) fbWidth / (float) winWidth;

            // Update and render
            glViewport(0, 0, fbWidth, fbHeight);
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

//            double t = glfwGetTime();


            nvgBeginFrame(nvgContext, winWidth, winHeight, pxRatio);
            VS_CONTEXT.beginFrame();
            //ui here
            render(nvgContext, winWidth, winHeight);
            perfFps->render();
            perfCpu->render();
            nvgEndFrame(nvgContext);
            VS_CONTEXT.endFrame();
            if (isPerf) {
                cpuTime = glfwGetTime() - t;
                perfFps->updateGraph(dt);
                perfCpu->updateGraph(cpuTime);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        nvgDeleteGL3(nvgContext);
        glfwTerminate();
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

    void close() {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    void minimize() {
        glfwIconifyWindow(window);
    }

    void maximize() {
    }

    void moveWindow(int dx, int dy) {
        int wx, wy;
        glfwGetWindowPos(window, &wx, &wy);
        glfwSetWindowPos(window, wx + dx, wy + dy);
    }

    unsigned int buttons;
    int mods;
    int enabeld;
    int action;
    int renderIdx;

    void beginFrame() {
//        renderIdx = 0;
    }

    int width;
    int height;

    void render(NVGcontext *vg, int w, int h) {
        if (this->width != w || this->height != h) {
            this->width = w;
            this->height = h;
            disEvent(VsEvent::RESIZE);

        }
        disEvent(VsEvent::RENDER);
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
            disEvent(VsEvent::STAGE_MOUSE_DOWN);
        else if (act == GLFW_RELEASE)
            disEvent(VsEvent::STAGE_MOUSE_UP);
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

void mousebutton(GLFWwindow *window, int button, int action, int mods) {
    NVG_NOTUSED(window);
    switch (button) {
        case 1:
            button = 2;
            break;
        case 2:
            button = 1;
            break;
    }
    cout << "button:" << button << "action:" << action << "mods:" << mods << endl;
    VsContext::_().setMouseButton(button, mods, action);
}

void cursorpos(GLFWwindow *window, double x, double y) {
    NVG_NOTUSED(window);
    VsContext::_().setCursor(x, y);
}