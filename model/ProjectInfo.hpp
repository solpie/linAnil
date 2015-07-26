#pragma once
#include "string"
#include "CompositionInfo.hpp"

class ProjectInfo {
public:
    ProjectInfo() {
        _comps = new vector<CompositionInfo *>;
    }

    string name;
    vector<CompositionInfo *> *_comps;

    void save(string path) {

    }

    CompositionInfo *curCompInfo = nullptr;

    void newComposition(string name, int width, int height, int frameRate, int duration) {
        CompositionInfo *comp = new CompositionInfo();
        comp->name = name;
        comp->width = width;
        comp->height = height;
        comp->frameRate = frameRate;
        comp->durationFrame = duration;
        if (!curCompInfo)
            curCompInfo = comp;
    }
};