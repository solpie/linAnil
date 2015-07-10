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

#define BLENDISH_IMPLEMENTATION

#include "oui/blendish.h"

#define OUI_IMPLEMENTATION

#include "oui/oui.h"
#include "ui.hpp"

using namespace std;


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
    MainWin(){
        Evt_add("test",testThread);
    }
    void testThread(void *e){
        cout<<this<<"thread safe"<<endl;
    }
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

    void start() {
        std::thread t([this] { this->show(); });
        t.detach();
    }

private:
    void build_democontent(int parent) {
        // some persistent variables for demonstration
        static float progress1 = 0.25f;
        static float progress2 = 0.75f;
        static int option1 = 1;
        static int option2 = 0;
        static int option3 = 0;

        int col = column();
        uiInsert(parent, col);
        uiSetMargins(col, 10, 10, 10, 10);
        uiSetLayout(col, UI_TOP | UI_HFILL);
        column_append(col, button(BND_ICON_GHOST, "Item 1", demohandler));
//        if (option3)
        column_append(col, button(BND_ICON_GHOST, "Item 2", demohandler));

//        {
//            int h = column_append(col, hbox());
//            hgroup_append(h, radio(BND_ICON_GHOST, "Item 3.0", &enum1));
//            if (option2)
//                uiSetMargins(hgroup_append_fixed(h, radio(BND_ICON_REC, NULL, &enum1)), -1,0,0,0);
//            uiSetMargins(hgroup_append_fixed(h, radio(BND_ICON_PLAY, NULL, &enum1)), -1,0,0,0);
//            uiSetMargins(hgroup_append(h, radio(BND_ICON_GHOST, "Item 3.3", &enum1)), -1,0,0,0);
//        }
//
//        {
//            int rows = column_append(col, row());
//            int coll = row_append(rows, vgroup());
//            vgroup_append(coll, label(-1, "Items 4.0:"));
//            coll = vgroup_append(coll, vbox());
//            vgroup_append(coll, button(BND_ICON_GHOST, "Item 4.0.0", demohandler));
//            uiSetMargins(vgroup_append(coll, button(BND_ICON_GHOST, "Item 4.0.1", demohandler)),0,-2,0,0);
//            int colr = row_append(rows, vgroup());
//            uiSetMargins(colr, 8, 0, 0, 0);
//            uiSetFrozen(colr, option1);
//            vgroup_append(colr, label(-1, "Items 4.1:"));
//            colr = vgroup_append(colr, vbox());
//            vgroup_append(colr, slider("Item 4.1.0", &progress1));
//            uiSetMargins(vgroup_append(colr, slider("Item 4.1.1", &progress2)),0,-2,0,0);
//        }
//
//        column_append(col, button(BND_ICON_GHOST, "Item 5", NULL));
//
//        static char textbuffer[1024] = "The quick brown fox.";
//        column_append(col, textbox(textbuffer, 1024));
//
//        column_append(col, check("Frozen", &option1));
//        column_append(col, check("Item 7", &option2));
//        column_append(col, check("Item 8", &option3));
    }

    int panel() {
        int item = uiItem();
        UIData *data = (UIData *) uiAllocHandle(item, sizeof(UIData));
        data->subtype = ST_PANEL;
        data->handler = NULL;
        return item;
    }

    struct NVGcontext *_vg = nullptr;

    void init(NVGcontext *vg) {
        bndSetFont(nvgCreateFont(vg, "system", "oui/DejaVuSans.ttf"));
        bndSetIconImage(nvgCreateImage(vg, "oui/blender_icons16.png", 0));
    }


    void draw(NVGcontext *vg, int w, int h) {
        bndBackground(vg, 0, 0, w, h);

        // some OUI stuff
        uiBeginLayout();

        int root = panel();
        // position root element
        uiSetSize(0, w, h);
        ((UIData *) uiGetHandle(root))->handler = roothandler;
        uiSetEvents(root, UI_SCROLL | UI_BUTTON0_DOWN);
        uiSetBox(root, UI_COLUMN);

        static int choice = -1;

        int menu = uiItem();
        uiSetLayout(menu, UI_HFILL | UI_TOP);
        uiSetBox(menu, UI_ROW);
        uiInsert(root, menu);

//        int opt_oui_demo = add_menu_option(menu, "OUI Demo", &choice);

        int content = uiItem();
        uiSetLayout(content, UI_FILL);
        uiInsert(root, content);

//    if (choice == opt_blendish_demo) {
//        int democontent = uiItem();
//        uiSetLayout(democontent, UI_FILL);
//        uiInsert(content, democontent);
//
//        UIData *data = (UIData *)uiAllocHandle(democontent, sizeof(UIData));
//        data->handler = 0;
//        data->subtype = ST_DEMOSTUFF;
//    }
//    else
//        if (choice == opt_oui_demo) {
        int democontent = uiItem();
        uiSetLayout(democontent, UI_TOP);
        uiSetSize(democontent, 250, 0);
        uiInsert(content, democontent);
        build_democontent(democontent);
//        }

        uiEndLayout();

        drawUI(vg, 0, BND_CORNER_NONE);
#if 0
    for (int i = 0; i < uiGetLastItemCount(); ++i) {
        if (uiRecoverItem(i) == -1) {
            UIitem *pitem = uiLastItemPtr(i);
            nvgBeginPath(vg);
            nvgRect(vg,pitem->margins[0],pitem->margins[1],pitem->size[0],pitem->size[1]);
            nvgStrokeWidth(vg, 2);
            nvgStrokeColor(vg, nvgRGBAf(1.0f,0.0f,0.0f,0.5f));
            nvgStroke(vg);
        }
    }
#endif


        uiProcess((int) (glfwGetTime() * 1000.0));
    }
};