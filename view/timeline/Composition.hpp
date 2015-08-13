#pragma once
//
// Created by toramisu on 2015/8/13.
//

#include <model/CompositionInfo.hpp>
#include <events/Evt.hpp>
#include "VsObjContainer.hpp"
#include "BaseTrack.hpp"
#include "Track.hpp"
#include "AudioTrack.hpp"

class Composition : public VsObjContainer {
public:
    Composition(CompositionInfo *compositionInfo) {
        _compInfo = compositionInfo;

        add_event_on(_compInfo, TrackModelEvent::NEW_TRACK, onNewTrack);
    }

    virtual void setSize(int w, int h) override {
        VsObj::setSize(w, -1);
        if (headTrack)
            headTrack->foreach([this](Track *track) {
                track->width = width;
            });
    }

    void scrollV(int v) {
        int vy = v;
        if (headTrack) {
            headTrack->setY(-vy);
            vy = 0;
            headTrack->foreach([&](BaseTrack *track) {
                if (vy) {
                    track->setY(vy);
                }
                vy = track->y() + track->height;
            });
        }

    }

    void scrollH(int v) {
        if (headTrack)
            headTrack->foreach([&](BaseTrack *track) {
                track->scrollX(v);
            });
    }

    int getCompInfoIdx() {
        return _compInfo->idx;
    }

protected:
    BaseTrack *headTrack = nullptr;
private:
    CompositionInfo *_compInfo;
    Track *selectTrack = nullptr;

    void onSelTrack(void *e) {
        if (selectTrack)
            selectTrack->setSelected(false);
        selectTrack = get_dispatcher(Track);
    }

    void onNewTrack(void *e) {
        BaseTrackInfo *trkInfob = get_paylaod(BaseTrackInfo);
        BaseTrack *newBaseTrack;
        if (trkInfob->type == TrackType::Image) {
            TrackInfo *trackInfo = get_paylaod(TrackInfo);
            Track *newTrack = new Track(trackInfo);
            newBaseTrack = newTrack;
        }
        else if (trkInfob->type == TrackType::Audio) {
            AudioTrackInfo *audioTrackInfo = get_paylaod(AudioTrackInfo);
            AudioTrack *audioTrack = new AudioTrack(audioTrackInfo);
            newBaseTrack = audioTrack;
        }


        add_event_on(newBaseTrack, VsEvent::SELECTED, onSelTrack);
        addChild(newBaseTrack);
        if (!headTrack) {
            headTrack = newBaseTrack;
        }
        else {
            BaseTrack *tail = headTrack->getTail();
            newBaseTrack->setY(tail->y() + tail->height);
            newBaseTrack->setPre(tail);
        }

        newBaseTrack->width = width;

        int totalHeight = 0;
        headTrack->foreach([&](BaseTrack *track) {
            totalHeight += track->height;
        });
        height = totalHeight;
        disEvent(VsEvent::CHANGED);
    }

};

