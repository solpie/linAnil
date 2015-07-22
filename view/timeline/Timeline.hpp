#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_TIMELINE_HPP
#define LINANIL_TIMELINE_HPP

#endif //LINANIL_TIMELINE_HPP


#include <model/TrackInfo.hpp>
#include "events/Event.hpp"
#include <events/TrackModelEvent.hpp>
#include <vs/ScrollBar.hpp>
#include <model/App.hpp>
#include "vs/Slider.hpp"
#include "TrackToolBar.hpp"
#include "Track.hpp"
#include "TimestampBar.hpp"

class Timeline : public VsObjContainer {
public:
    Timeline() {
        trackToolBar = new TrackToolBar();
        addChild(trackToolBar);

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

        Evt_add(TrackModelEvent::NEW_TRACK, onNewTrack)
    }

    Track *selectTrack = nullptr;

    void onScrollV(void *e) {
        int vy = vScrollBar->getValue();
        headTrack->setY(trackToolBar->height - vy);
        vy = 0;
        headTrack->foreach([&](Track *track) {
            if (vy) {
                track->setY(vy);
            }
            vy = track->y() + track->height;
        });
    }

    void onScrollH(void *e) {
        headTrack->foreach([this](Track *track) {
            track->scrollX(timestampBar->getValue());
        });
    }

    void onSelTrack(void *e) {
        if (selectTrack)
            selectTrack->setSelected(false);
        selectTrack = get_dispatcher(Track);
    }

    void onNewTrack(TrackInfo *trackInfo) {
        Track *newTrack = new Track(trackInfo);
//        newTrack->setHideY(trackToolBar->height);
        add_event_on(newTrack, VsEvent::SELECTED, onSelTrack)
        addChildAt(newTrack, 0);
        if (!headTrack) {
            headTrack = newTrack;
            newTrack->setY(trackToolBar->height);
        }
        else {
            Track *tail = headTrack->getTail();
            newTrack->setY(tail->y() + tail->height);
            newTrack->setPre(tail);
        }
        int totalHeight = 0;
        headTrack->foreach([&](Track *track) {
            totalHeight += track->height;
        });
        vScrollBar->setContent(totalHeight);
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

    virtual void render() override {
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, nvgRGB(29, 29, 29));
        //
        nvgFill(vg);
        if (_trackInfo)
            renderTrackInfo(_trackInfo);

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
        headTrack->foreach([this](Track *track) {
            track->width = width;
        });
        vScrollBar->setSize(-1, h - trackToolBar->height);
        timestampBar->setSize(w - TIMELINE_TRACK_PANEL_DEF_WIDTH, h);
    }


private:
    TrackToolBar *trackToolBar;
//    Track *t;
    Track *headTrack = nullptr;
    TrackInfo *_trackInfo = nullptr;
    ScrollBar *vScrollBar;
    TimestampBar *timestampBar;

    void renderTrackInfo(TrackInfo *trackInfo) {
        if (trackInfo->next)
            renderTrackInfo(trackInfo->next);
    }
};

