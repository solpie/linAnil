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
#include <vs/events/KeyEvent.hpp>
#include "VsObj.hpp"

#define VG_CONTEXT  VsContext::_().getContext()
#define VS_CONTEXT VsContext::_()
#define add_event_on_context(type, func) VS_CONTEXT.add_event(type,func);

#include "events/EventDispatcher.hpp"
#include "events/BaseEvent.hpp"
#include "Performance.hpp"

#define VS_WIDTH 1440
#define VS_HEIGHT 920

#include "windows.h"

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

void mouseButton(GLFWwindow *window, int button, int action, int mods);

void cursorPos(GLFWwindow *window, double x, double y);

void key(GLFWwindow *window, int key, int scancode, int action, int mods);

void scrollevent(GLFWwindow *window, double x, double y) {
    NVG_NOTUSED(window);
//    uiSetScroll((int) x, (int) y);
}

void charevent(GLFWwindow *window, unsigned int value) {
    NVG_NOTUSED(window);
//    uiSetChar(value);
}


class VsContext : public EventDispatcher, public S<VsContext> {
public:
    Performance *perfFps;
    Performance *perfCpu;
//    int screenWidth;
//    int screenHeight;
    HWND actWindow;
    long normalStyle;
    long noBorderStyle;
    bool isMaximized = false;
    int lastWidth;
    int lastHeight;

    void initVsContext() {
        actWindow = GetActiveWindow();


        long Style = GetWindowLong(actWindow, GWL_STYLE);
        normalStyle = Style;
        Style &= ~(0x00C00000L |
                   0x00C0000L); //this makes it still work when WS_MAXIMIZEBOX is actually already toggled off
//        Style &= ~WS_CAPTION;
        noBorderStyle = Style;
        SetWindowLong(actWindow, GWL_STYLE, Style);

//        long Style = GetWindowLong(actWindow, GWL_STYLE);
//        Style &= ~WS_MAXIMIZEBOX; //this makes it still work when WS_MAXIMIZEBOX is actually already toggled off
//        SetWindowLong(actWindow, GWL_STYLE, Style);
//        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
//        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
//        screenWidth = mode->width;
//        screenHeight = mode->height;
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
//        glfwWindowHint(GLFW_DECORATED, false);




        _window = glfwCreateWindow(VS_WIDTH, VS_HEIGHT, "", nullptr, nullptr);
        if (!_window) {
            glfwTerminate();
//            return -1;
        }
        glfwSetKeyCallback(_window, key);
        glfwSetCharCallback(_window, charevent);
        glfwSetCursorPosCallback(_window, cursorPos);
        glfwSetMouseButtonCallback(_window, mouseButton);
        glfwSetScrollCallback(_window, scrollevent);

        glfwMakeContextCurrent(_window);
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

        initVsContext();

        //limit fps to monitor on=1 off=0
//        glfwSwapInterval(0);
        glfwSwapInterval(1);

        glfwSetTime(0);

        double c = 0.0;
        int total = 0;
        bool isPerf = true;
//        if (isPerf) {
        double prevt = 0, cpuTime = 0;
//        }

        while (!glfwWindowShouldClose(_window)) {
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


            glfwGetCursorPos(_window, &mx, &my);
            glfwGetWindowSize(_window, &winWidth, &winHeight);
            glfwGetFramebufferSize(_window, &fbWidth, &fbHeight);
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

            glfwSwapBuffers(_window);
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
        glfwSetWindowShouldClose(_window, GL_TRUE);
    }

    void minimize() {
        glfwIconifyWindow(_window);
    }

    void maximize() {
        if (isMaximized) {
            SetWindowLong(actWindow, GWL_STYLE, noBorderStyle);
            glfwSetWindowSize(_window, lastWidth, lastHeight);
        }
        else {
            lastWidth = width;
            lastHeight = height;
            SetWindowLong(actWindow, GWL_STYLE, normalStyle);
            ShowWindow(actWindow, SW_MAXIMIZE);
            SetWindowLong(actWindow, GWL_STYLE, normalStyle & ~WS_CAPTION);
        }
        isMaximized = !isMaximized;
    }

    void moveWindow(int dx, int dy) {
        RECT r;
        GetWindowRect(actWindow, &r);
        MoveWindow(actWindow, r.left + dx, r.top + dy, width, height, TRUE);
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

    int _curCursor = 0;
    map<int, GLFWcursor *> _mapCursor;

    void setCursor(int v) {
        if (_curCursor != v) {
            _curCursor = v;
            if (_mapCursor.find(v) == _mapCursor.end())
                _mapCursor[v] = glfwCreateStandardCursor(v);
            glfwSetCursor(_window, _mapCursor[v]);
        }
    }

    void setCursorPos(int x, int y) {
        glfwSetCursorPos(_window, x, y);
    }

    void hideCursor() {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    }

    void showCursor() {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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


    void setKey(int key, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(_window, GL_TRUE);
        }
        KeyEvent *keyEvent = new KeyEvent();
        keyEvent->key = key;
        if (action == GLFW_PRESS) {
            keyEvent->type = KeyEvent::DOWN;
        }
        else if (action == GLFW_RELEASE) {
            keyEvent->type = KeyEvent::UP;
        }
        disEvent(*keyEvent);
        cout << typeid(this).name() << " key " << key << " mods " << mods << endl;
    }

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
    GLFWwindow *_window;
    map<string, BaseEvent> _uiEvents;
    NVGcontext *nvgContext = nullptr;
};

void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    NVG_NOTUSED(window);
    switch (button) {
        case 1:
            button = 2;
            break;
        case 2:
            button = 1;
            break;
    }
    VsContext::_().setMouseButton(button, mods, action);
}

void cursorPos(GLFWwindow *window, double x, double y) {
    NVG_NOTUSED(window);
    VsContext::_().setCursor(x, y);
}

void key(GLFWwindow *window, int key, int scancode, int action, int mods) {
    NVG_NOTUSED(scancode);

    VsContext::_().setKey(key, action, mods);
//    uiSetKey(key, mods, action);
}