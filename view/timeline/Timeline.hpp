#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_TIMELINE_HPP
#define LINANIL_TIMELINE_HPP

#endif //LINANIL_TIMELINE_HPP


#include "vs/Slider.hpp"
#include "TrackToolBar.hpp"
#include "Track.hpp"

class Timeline : public VsObjContainer {
public:
    Timeline() {
        trackToolBar = new TrackToolBar();
        addChild(trackToolBar);

        t = new Track();
        t->setY(trackToolBar->height);
        addChild(t);
    }

    virtual void render() override;

private:
    TrackToolBar *trackToolBar;
    Track *t;
};

void Timeline::render() {
    NVGcontext *vg = nvgContext;
    nvgBeginPath(vg);
    nvgRect(vg, gX(), gY(), width, height);
    nvgFillColor(vg, nvgRGBA(72, 72, 72, 255));
    nvgFill(vg);
    VsObjContainer::render();
}
