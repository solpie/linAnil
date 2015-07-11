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

class Performance : public VsObj {
public:
    Performance() : VsObj() {
        fps = new PerfGraph();
        width = 200;
        height = 35;
//        cpuGraph = new PerfGraph();
//        gpuGraph = new PerfGraph();
    }

    PerfGraph *fps, *cpuGraph, *gpuGraph;

//private:
    virtual void render() override;

//    void update() {
//        renderGraph(vg, 5,5, &fps);
//        renderGraph(vg, 5+200+5,5, &cpuGraph);
//        if (gpuTimer.supported)
//            renderGraph(vg, 5+200+5+200+5,5, &gpuGraph);
//    }

};

//void renderGraph(NVGcontext *vg, float x, float y, PerfGraph *fps) {
//    int i;
//    float avg, w, h;
//    char str[64];
//
//    avg = getGraphAverage(fps);
//
//    w = 200;
//    h = 35;
//
//    nvgBeginPath(vg);
//    nvgRect(vg, x, y, w, h);
//    nvgFillColor(vg, nvgRGBA(0, 0, 0, 128));
//    nvgFill(vg);
//
//    nvgBeginPath(vg);
//    nvgMoveTo(vg, x, y + h);
//    if (fps->style == GRAPH_RENDER_FPS) {
//        for (i = 0; i < GRAPH_HISTORY_COUNT; i++) {
//            float v = 1.0f / (0.00001f + fps->values[(fps->head + i) % GRAPH_HISTORY_COUNT]);
//            float vx, vy;
//            if (v > 80.0f) v = 80.0f;
//            vx = x + ((float) i / (GRAPH_HISTORY_COUNT - 1)) * w;
//            vy = y + h - ((v / 80.0f) * h);
//            nvgLineTo(vg, vx, vy);
//        }
//    } else if (fps->style == GRAPH_RENDER_PERCENT) {
//        for (i = 0; i < GRAPH_HISTORY_COUNT; i++) {
//            float v = fps->values[(fps->head + i) % GRAPH_HISTORY_COUNT] * 1.0f;
//            float vx, vy;
//            if (v > 100.0f) v = 100.0f;
//            vx = x + ((float) i / (GRAPH_HISTORY_COUNT - 1)) * w;
//            vy = y + h - ((v / 100.0f) * h);
//            nvgLineTo(vg, vx, vy);
//        }
//    } else {
//        for (i = 0; i < GRAPH_HISTORY_COUNT; i++) {
//            float v = fps->values[(fps->head + i) % GRAPH_HISTORY_COUNT] * 1000.0f;
//            float vx, vy;
//            if (v > 20.0f) v = 20.0f;
//            vx = x + ((float) i / (GRAPH_HISTORY_COUNT - 1)) * w;
//            vy = y + h - ((v / 20.0f) * h);
//            nvgLineTo(vg, vx, vy);
//        }
//    }
//    nvgLineTo(vg, x + w, y + h);
//    nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
//    nvgFill(vg);
//
//    nvgFontFace(vg, "sans");
//
//    if (fps->name[0] != '\0') {
//        nvgFontSize(vg, 14.0f);
//        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
//        nvgFillColor(vg, nvgRGBA(240, 240, 240, 192));
//        nvgText(vg, x + 3, y + 1, fps->name, nullptr);
//    }
//
//    if (fps->style == GRAPH_RENDER_FPS) {
//        nvgFontSize(vg, 18.0f);
//        nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
//        nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
//        sprintf(str, "%.2f FPS", 1.0f / avg);
//        nvgText(vg, x + w - 3, y + 1, str, NULL);
//
//        nvgFontSize(vg, 15.0f);
//        nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
//        nvgFillColor(vg, nvgRGBA(240, 240, 240, 160));
//        sprintf(str, "%.2f ms", avg * 1000.0f);
//        nvgText(vg, x + w - 3, y + h - 1, str, NULL);
//    }
//    else if (fps->style == GRAPH_RENDER_PERCENT) {
//        nvgFontSize(vg, 18.0f);
//        nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
//        nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
//        sprintf(str, "%.1f %%", avg * 1.0f);
//        nvgText(vg, x + w - 3, y + 1, str, NULL);
//    } else {
//        nvgFontSize(vg, 18.0f);
//        nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
//        nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
//        sprintf(str, "%.2f ms", avg * 1000.0f);
//        nvgText(vg, x + w - 3, y + 1, str, NULL);
//    }
//}

void Performance::render() {
    int i;
    float avg, w, h;
    char str[64];
    NVGcontext *vg = this->nvgContext;
    avg = getGraphAverage(fps);

    w = width;
    h = height;

    nvgBeginPath(vg);
    nvgRect(vg, x, y, w, h);
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 128));
    nvgFill(vg);

    nvgBeginPath(vg);
    nvgMoveTo(vg, x, y + h);
    if (fps->style == GRAPH_RENDER_FPS) {
        for (i = 0; i < GRAPH_HISTORY_COUNT; i++) {
            float v = 1.0f / (0.00001f + fps->values[(fps->head + i) % GRAPH_HISTORY_COUNT]);
            float vx, vy;
            if (v > 80.0f) v = 80.0f;
            vx = x + ((float) i / (GRAPH_HISTORY_COUNT - 1)) * w;
            vy = y + h - ((v / 80.0f) * h);
            nvgLineTo(vg, vx, vy);
        }
    } else if (fps->style == GRAPH_RENDER_PERCENT) {
        for (i = 0; i < GRAPH_HISTORY_COUNT; i++) {
            float v = fps->values[(fps->head + i) % GRAPH_HISTORY_COUNT] * 1.0f;
            float vx, vy;
            if (v > 100.0f) v = 100.0f;
            vx = x + ((float) i / (GRAPH_HISTORY_COUNT - 1)) * w;
            vy = y + h - ((v / 100.0f) * h);
            nvgLineTo(vg, vx, vy);
        }
    } else {
        for (i = 0; i < GRAPH_HISTORY_COUNT; i++) {
            float v = fps->values[(fps->head + i) % GRAPH_HISTORY_COUNT] * 1000.0f;
            float vx, vy;
            if (v > 20.0f) v = 20.0f;
            vx = x + ((float) i / (GRAPH_HISTORY_COUNT - 1)) * w;
            vy = y + h - ((v / 20.0f) * h);
            nvgLineTo(vg, vx, vy);
        }
    }
    nvgLineTo(vg, x + w, y + h);
    nvgFillColor(vg, nvgRGBA(255, 192, 0, 128));
    nvgFill(vg);

    nvgFontFace(vg, "sans");

    if (fps->name[0] != '\0') {
        nvgFontSize(vg, 14.0f);
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgFillColor(vg, nvgRGBA(240, 240, 240, 192));
        nvgText(vg, x + 3, y + 1, fps->name, nullptr);
    }

    if (fps->style == GRAPH_RENDER_FPS) {
        nvgFontSize(vg, 18.0f);
        nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
        nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
        sprintf(str, "%.2f FPS", 1.0f / avg);
        nvgText(vg, x + w - 3, y + 1, str, NULL);

        nvgFontSize(vg, 15.0f);
        nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
        nvgFillColor(vg, nvgRGBA(240, 240, 240, 160));
        sprintf(str, "%.2f ms", avg * 1000.0f);
        nvgText(vg, x + w - 3, y + h - 1, str, NULL);
    }
    else if (fps->style == GRAPH_RENDER_PERCENT) {
        nvgFontSize(vg, 18.0f);
        nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
        nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
        sprintf(str, "%.1f %%", avg * 1.0f);
        nvgText(vg, x + w - 3, y + 1, str, NULL);
    } else {
        nvgFontSize(vg, 18.0f);
        nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
        nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
        sprintf(str, "%.2f ms", avg * 1000.0f);
        nvgText(vg, x + w - 3, y + 1, str, NULL);
    }
}
