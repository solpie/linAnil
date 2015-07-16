#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_TIMELINE_HPP
#define LINANIL_TIMELINE_HPP

#endif //LINANIL_TIMELINE_HPP


#include <model/TrackInfo.hpp>
#include <events/TrackModelEvent.hpp>
#include <vs/ScrollBar.hpp>
#include "vs/Slider.hpp"
#include "TrackToolBar.hpp"
#include "Track.hpp"

class Timeline : public VsObjContainer {
public:
    Timeline() {
        trackToolBar = new TrackToolBar();
        addChild(trackToolBar);

//        t = new Track();
//        t->setY(trackToolBar->height);
//        addChild(t);
//        cout << this << "init Timeline" << endl;
        hScrollBar = new ScrollBar(Direction::Horizontal);
        hScrollBar->move(250, 300);
        hScrollBar->width = 250;
        hScrollBar->height = 15;
        addChild(hScrollBar);

//        Direction::Vertical;
        vScrollBar = new ScrollBar(Direction::Vertical);
        vScrollBar->move(250, trackToolBar->height);
        vScrollBar->width = 15;
        vScrollBar->height = 250;
        addChild(vScrollBar);

        Evt_add(TrackModelEvent::NEW_TRACK, onNewTrack)
    }

    Track *selectTrack = nullptr;

    void onSelTrack(void *e) {
        if (selectTrack)
            selectTrack->setSelected(false);
        selectTrack = getTarget(VsEvent,Track);

    }

    void onNewTrack(TrackInfo *trackInfo) {
        Track *newTrack = new Track(trackInfo);
//        addChild(newTrack);
        addEventOn(newTrack,VsEvent::SELECTED,onSelTrack)

        addChildAt(newTrack, 0);
        if (!headTrack) {
            headTrack = newTrack;
            newTrack->setY(trackToolBar->height);
        }
        else {
            Track *tail = headTrack->getTail();
            newTrack->setY(tail->gY() + tail->height);
            newTrack->setPre(tail);
        }
    }

    void setTrackInfo(TrackInfo *trackInfo) {
        _trackInfo = trackInfo;
        TrackInfo *t = trackInfo;
        Track *trk;
        Track *preTrack = nullptr;
        while (t) {
            trk = new Track(trackInfo);
            if (preTrack)
                trk->setY(preTrack->gY() + preTrack->height);
            else
                trk->setY(trackToolBar->height);
            addChild(trk);
            preTrack = trk;
            t = t->next;
        }
    }


    virtual void render() override;

private:
    TrackToolBar *trackToolBar;
    Track *t;
    Track *headTrack = nullptr;
    TrackInfo *_trackInfo = nullptr;
    ScrollBar *hScrollBar;
    ScrollBar *vScrollBar;

    void renderTrackInfo(TrackInfo *trackInfo) {
        NVGcontext *vg = nvgContext;

        if (trackInfo->next)
            renderTrackInfo(trackInfo->next);
    }
};

void Timeline::render() {
    NVGcontext *vg = nvgContext;
    nvgBeginPath(vg);
    nvgRect(vg, gX(), gY(), width, height);
    nvgFillColor(vg, nvgRGBA(72, 72, 72, 255));
    nvgFill(vg);
    if (_trackInfo)
        renderTrackInfo(_trackInfo);

    VsObjContainer::render();
}
