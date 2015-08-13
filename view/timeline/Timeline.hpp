#pragma once
//
// Created by manoyuria on 2015/7/11.
//


#include <model/TrackInfo.hpp>
#include "events/Evt.hpp"
#include <events/TrackModelEvent.hpp>
#include <vs/ScrollBar.hpp>
#include <model/App.hpp>
#include "vs/Slider.hpp"
#include "TrackToolBar.hpp"
#include "Track.hpp"
#include "TimestampBar.hpp"
#include "AudioTrack.hpp"
#include "CompTabs.hpp"
#include "Composition.hpp"

class Timeline : public VsObjContainer {
public:
    Timeline() {
        trackToolBar = new TrackToolBar();
        addChild(trackToolBar);

        curComposition = new Composition(_proj->curCompInfo);
        curComposition->setY(trackToolBar->height);
        add_event_on(curComposition, VsEvent::CHANGED, onChangeHeight);
        addChildAt(curComposition, 0);

        timestampBar = new TimestampBar();
        timestampBar->setX(TIMELINE_TRACK_PANEL_DEF_WIDTH);
        add_event_on(timestampBar, VsEvent::CHANGED, onScrollH)
        addChild(timestampBar);

        vScrollBar = new ScrollBar(Direction::Vertical);
        vScrollBar->move(TIMELINE_TRACK_PANEL_DEF_WIDTH - 15, trackToolBar->height);
        vScrollBar->width = 15;
        vScrollBar->height = 250;
        add_event_on(vScrollBar, VsEvent::CHANGED, onScrollV)

        addChild(vScrollBar);
    }


    void onChangeHeight(void *e) {
        vScrollBar->setContent(curComposition->height);
    }

    void onScrollV(void *e) {
        curComposition->scrollV(vScrollBar->getValue());
    }

    void onScrollH(void *e) {
        curComposition->scrollH(timestampBar->getValue());
    }

    virtual void render() override {
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, nvgRGB(29, 29, 29));
        //
        nvgFill(vg);

        VsObjContainer::render();
        {//border
            nvgBeginPath(vg);
            nvgRect(vg, gX() + TIMELINE_TRACK_PANEL_DEF_WIDTH - 3, gY(), 3, height);
            nvgFillColor(vg, nvgRGB(29, 29, 29));
            nvgFill(vg);
        }

    }

    void setSize(int w, int h) override {
        VsObj::setSize(w, h);
        curComposition->setSize(w, h);
        timestampBar->setSize(w - TIMELINE_TRACK_PANEL_DEF_WIDTH, h);
        vScrollBar->setSize(-1, h - trackToolBar->height);
    }


private:
    Composition *curComposition;
    TrackToolBar *trackToolBar;
    ScrollBar *vScrollBar;
    TimestampBar *timestampBar;
};

