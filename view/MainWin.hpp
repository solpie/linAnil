//
// Created by toramisu on 2015/7/10.
//
#pragma once
#ifndef LINANIL_MAINWIN_HPP
#define LINANIL_MAINWIN_HPP

#endif //LINANIL_MAINWIN_HPP

#include <stdio.h>

#ifdef NANOVG_GLEW

#include <GL/glew.h>

#endif
#ifdef __APPLE__
#	define GLFW_INCLUDE_GLCOREARB
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <c++/4.9.2/thread>
#include "nanovg/nanovg.h"

#define NANOVG_GL3_IMPLEMENTATION

#include "nanovg/nanovg_gl.h"
#include "UI.hpp"
#include "Performance.hpp"
#include "vs/VsContext.hpp"
#include "vs/VsObjContainer.hpp"
#include "VsRoot.hpp"

using namespace std;


void errorcb(int error, const char *desc) {
    cout << "GLFW error " << error << ": " << desc << endl;
}

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

class MainWin {
public:
    Performance *perfFps;
    Performance *perfCpu;

    MainWin() {
        perfFps = new Performance();
        perfFps->setX(5);
        perfFps->setY(5);
        perfFps->initGraph(GRAPH_RENDER_FPS, "Frame Time");
//        addChild(perfFps);

        perfCpu = new Performance();
        perfCpu->setX(perfFps->gX() + perfFps->width + 5);
        perfCpu->setY(5);
        perfCpu->initGraph(GRAPH_RENDER_MS, "CPU Time");
//        addChild(perfCpu);
        Evt_add("test", testThread);
    }

    void testThread(void *e) {
        cout << this << "thread safe" << endl;
    }

    int show() {
        GLFWwindow *window;

        if (!glfwInit()) {
            printf("Failed to init GLFW.");
            return -1;
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
//        glfwWindowHint(GLFW_REFRESH_RATE, 60);
//        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        //no title bar no border
//        glfwWindowHint(GLFW_DECORATED, false);

        window = glfwCreateWindow(1440, 920, "linAnil", nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            return -1;
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
            return -1;
        }
        // GLEW generates GL error because it calls glGetString(GL_EXTENSIONS), we'll consume it here.
        glGetError();
#endif
        ////////////////////////vg

        _vg = VsContext::_().init();
        if (_vg == NULL) {
            printf("Could not init nanovg.\n");
            return -1;
        }

        init(_vg);
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


            nvgBeginFrame(_vg, winWidth, winHeight, pxRatio);
            VS_CONTEXT.beginFrame();
            //ui here
            render(_vg, winWidth, winHeight);
            perfFps->render();
            perfCpu->render();
            nvgEndFrame(_vg);
            VS_CONTEXT.endFrame();
            if (isPerf) {
                cpuTime = glfwGetTime() - t;
                perfFps->updateGraph(dt);
                perfCpu->updateGraph(cpuTime);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        nvgDeleteGL3(_vg);
        glfwTerminate();
        isClose = true;
        return 0;
    }

    void start() {
        std::thread t([this] { this->show(); });
        t.detach();
    }

    bool isClose;
private:

    struct NVGcontext *_vg = nullptr;
    VsRoot *vsRoot = nullptr;
    struct DemoData {
        int fontNormal, fontBold, fontIcons;
        int images[12];
    };
    typedef struct DemoData DemoData;

    void init(NVGcontext *vg) {
        //// init font icons
        nvgCreateFont(vg, "icons", "fonts/entypo.ttf");
        nvgCreateFont(vg, "sans", "fonts/Roboto-Regular.ttf");
        nvgCreateFont(vg, "sans-bold", "fonts/Roboto-Bold.ttf");
        (nvgCreateFont(vg, "system", "oui/DejaVuSans.ttf"));
        (nvgCreateImage(vg, "oui/blender_icons16.png", 0));
        //////////////////////////////////////////////
        vsRoot = new VsRoot();
    }


    void render(NVGcontext *vg, int w, int h) {
        if (vsRoot->width != w || vsRoot->height != h) {
            vsRoot->width = w;
            vsRoot->height = h;
            vsRoot->resize(w, h);
        }
        vsRoot->render();
    }
};