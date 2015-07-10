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
#include "nanovg.h"

#define NANOVG_GL3_IMPLEMENTATION

#include "nanovg_gl.h"

#define BLENDISH_IMPLEMENTATION

#include "oui/blendish.h"

#define OUI_IMPLEMENTATION

#include "oui/oui.h"

using namespace std;
typedef struct {
    int subtype;
    UIhandler handler;
} UIData;

void ui_handler(int item, UIevent event) {
    UIData *data = (UIData *) uiGetHandle(item);
    if (data && data->handler) {
        data->handler(item, event);
    }
}

void errorcb(int error, const char *desc) {
//    printf("GLFW error %d: %s\n", error, desc);
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
    uiSetButton(button, mods, (action == GLFW_PRESS) ? 1 : 0);
}

void cursorpos(GLFWwindow *window, double x, double y) {
    NVG_NOTUSED(window);
    uiSetCursor((int) x, (int) y);
}

void scrollevent(GLFWwindow *window, double x, double y) {
    NVG_NOTUSED(window);
    uiSetScroll((int) x, (int) y);
}

void charevent(GLFWwindow *window, unsigned int value) {
    NVG_NOTUSED(window);
    uiSetChar(value);
}

void key(GLFWwindow *window, int key, int scancode, int action, int mods) {
    NVG_NOTUSED(scancode);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    uiSetKey(key, mods, action);
}

class MainWin {
public:
    int show() {
        GLFWwindow *window;
        UIcontext *uictx;

        uictx = uiCreateContext(4096, 1 << 20);
        uiMakeCurrent(uictx);
        uiSetHandler(ui_handler);

        if (!glfwInit()) {
            printf("Failed to init GLFW.");
            return -1;
        }
//        glfwSetErrorCallback([this](int error, const char *desc) { this->errorcb(error, desc); });
        glfwSetErrorCallback(errorcb);

#ifndef _WIN32 // don't require this on win32, and works with more cards
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

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
        //_vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
        _vg = nvgCreateGL3(NVG_ANTIALIAS);
        if (_vg == NULL) {
            printf("Could not init nanovg.\n");
            return -1;
        }

        init(_vg);
        glfwSwapInterval(0);

        glfwSetTime(0);

        double c = 0.0;
        int total = 0;

        int peak_items = 0;
        unsigned int peak_alloc = 0;

        while (!glfwWindowShouldClose(window)) {
            double mx, my;
            int winWidth, winHeight;
            int fbWidth, fbHeight;
            float pxRatio;

            glfwGetCursorPos(window, &mx, &my);
            glfwGetWindowSize(window, &winWidth, &winHeight);
            glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
            // Calculate pixel ration for hi-dpi devices.
            pxRatio = (float) fbWidth / (float) winWidth;

            // Update and render
            glViewport(0, 0, fbWidth, fbHeight);
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            double t = glfwGetTime();
            nvgBeginFrame(_vg, winWidth, winHeight, pxRatio);

            draw(_vg, winWidth, winHeight);
            peak_items = (peak_items > uiGetItemCount()) ? peak_items : uiGetItemCount();
            peak_alloc = (peak_alloc > uiGetAllocSize()) ? peak_alloc : uiGetAllocSize();

            nvgEndFrame(_vg);
            double t2 = glfwGetTime();
            c += (t2 - t);
            total++;
            if (total > (60)) {
                cout << (c / (double) total) * 1000.0 << "ms" << endl;
                total = 0;
                c = 0.0;
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

private:
    struct NVGcontext *_vg = nullptr;

    void init(NVGcontext *vg) {
        bndSetFont(nvgCreateFont(vg, "system", "oui/DejaVuSans.ttf"));
        bndSetIconImage(nvgCreateImage(vg, "oui/blender_icons16.png", 0));
    }

    void draw(NVGcontext *vg, int w, int h) {

    }
};