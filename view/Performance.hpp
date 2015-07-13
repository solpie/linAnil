#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef KIUITEST_PROFILE_HPP
#define KIUITEST_PROFILE_HPP

#endif //KIUITEST_PROFILE_HPP

#include <stdio.h>
#include "nanovg/nanovg.h"
#include "vs/VsObj.hpp"
#include "vs/Sprite.hpp"

enum GraphrenderStyle {
    GRAPH_RENDER_FPS,
    GRAPH_RENDER_MS,
    GRAPH_RENDER_PERCENT,
};
#define GRAPH_HISTORY_COUNT 100
struct PerfGraph {
    int style;
    char name[32];
    float values[GRAPH_HISTORY_COUNT];
    int head;
};
typedef struct PerfGraph PerfGraph;

float getGraphAverage(PerfGraph *fps) {
    int i;
    float avg = 0;
    for (i = 0; i < GRAPH_HISTORY_COUNT; i++) {
        avg += fps->values[i];
    }
    return avg / (float) GRAPH_HISTORY_COUNT;
}

class Performance : public Sprite {
public:
    Performance() {
        fps = new PerfGraph();
        width = 200;
        height = 35;
        addEvent(MouseEvent::MOVE, onMove);
        addEvent(MouseEvent::DOWN, onDown);
        addEvent(MouseEvent::UP, onUp);
        addEvent(MouseEvent::ROLL_OVER, onRoll);
        addEvent(MouseEvent::ROLL_OUT, onRoll);
    }

    void onRoll(MouseEvent *e) {
//        Sprite *t = (Sprite *)e->target;
        cout << this << " Roll: " << e->type << endl;
        printf("roll");
    }
    void onDown(MouseEvent *e) {
        void *t = e->target;
        cout << this << " down: " << t << endl;
    }

    void onUp(MouseEvent *e) {
        void *t = e->target;
        cout << this << " : " << e->type << endl;
    }

    void onMove(MouseEvent *e) {
        void * t = e->target;
        cout << this << "move" <<t<< endl;
    }

    void initGraph(int style, const char *name) {
        memset(fps, 0, sizeof(PerfGraph));
        fps->style = style;
        strncpy(fps->name, name, sizeof(fps->name));
        fps->name[sizeof(fps->name) - 1] = '\0';
    }

    void updateGraph(float frameTime) {
        fps->head = (fps->head + 1) % GRAPH_HISTORY_COUNT;
        fps->values[fps->head] = frameTime;
    }

    PerfGraph *fps;

    virtual void onDraw() override {
        ///
        int i;
        float avg, w, h;
        char str[64];
        NVGcontext *vg = this->nvgContext;
        avg = getGraphAverage(fps);

        w = width;
        h = height;

        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), w, h);
        nvgFillColor(vg, nvgRGBA(0, 0, 0, 128));
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgMoveTo(vg, gX(), gY() + h);
        if (fps->style == GRAPH_RENDER_FPS) {
            for (i = 0; i < GRAPH_HISTORY_COUNT; i++) {
                float v = 1.0f / (0.00001f + fps->values[(fps->head + i) % GRAPH_HISTORY_COUNT]);
                float vx, vy;
                if (v > 80.0f) v = 80.0f;
                vx = gX() + ((float) i / (GRAPH_HISTORY_COUNT - 1)) * w;
                vy = gY() + h - ((v / 80.0f) * h);
                nvgLineTo(vg, vx, vy);
            }
        } else if (fps->style == GRAPH_RENDER_PERCENT) {
            for (i = 0; i < GRAPH_HISTORY_COUNT; i++) {
                float v = fps->values[(fps->head + i) % GRAPH_HISTORY_COUNT] * 1.0f;
                float vx, vy;
                if (v > 100.0f) v = 100.0f;
                vx = gX() + ((float) i / (GRAPH_HISTORY_COUNT - 1)) * w;
                vy = gY() + h - ((v / 100.0f) * h);
                nvgLineTo(vg, vx, vy);
            }
        } else {
            for (i = 0; i < GRAPH_HISTORY_COUNT; i++) {
                float v = fps->values[(fps->head + i) % GRAPH_HISTORY_COUNT] * 1000.0f;
                float vx, vy;
                if (v > 20.0f) v = 20.0f;
                vx = gX() + ((float) i / (GRAPH_HISTORY_COUNT - 1)) * w;
                vy = gY() + h - ((v / 20.0f) * h);
                nvgLineTo(vg, vx, vy);
            }
        }
        nvgLineTo(vg, gX() + w, gY() + h);
        nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
        nvgFill(vg);

        nvgFontFace(vg, "sans");

        if (fps->name[0] != '\0') {
            nvgFontSize(vg, 14.0f);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, nvgRGBA(240, 240, 240, 192));
            nvgText(vg, gX() + 3, gY() + 1, fps->name, nullptr);
        }

        if (fps->style == GRAPH_RENDER_FPS) {
            nvgFontSize(vg, 18.0f);
            nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
            nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
            sprintf(str, "%.2f FPS", 1.0f / avg);
            nvgText(vg, gX() + w - 3, gY() + 1, str, NULL);

            nvgFontSize(vg, 15.0f);
            nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
            nvgFillColor(vg, nvgRGBA(240, 240, 240, 160));
            sprintf(str, "%.2f ms", avg * 1000.0f);
            nvgText(vg, gX() + w - 3, gY() + h - 1, str, NULL);
        }
        else if (fps->style == GRAPH_RENDER_PERCENT) {
            nvgFontSize(vg, 18.0f);
            nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
            nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
            sprintf(str, "%.1f %%", avg * 1.0f);
            nvgText(vg, gX() + w - 3, gY() + 1, str, NULL);
        } else {
            nvgFontSize(vg, 18.0f);
            nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
            nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
            sprintf(str, "%.2f ms", avg * 1000.0f);
            nvgText(vg, gX() + w - 3, gY() + 1, str, NULL);
        }
        float cur = glfwGetTime();
        dt = cur - last;
        last = cur;
        updateGraph(dt);
    }

protected:
    float mx, my, last, dt;
};
