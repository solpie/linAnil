//
// Created by toramisu on 2015/7/10.
//
#pragma once

#ifndef LINANIL_TRACKMODEL2_HPP
#define LINANIL_TRACKMODEL2_HPP

#endif //LINANIL_TRACKMODEL2_HPP

#include "TrackInfo.hpp"
#include "vector"
#include "boost/filesystem.hpp"

#include "iostream"
#include "windows.h"

using namespace boost;

#include <stack>
#include <view/Theme.hpp>
#include "events/TrackModelEvent.hpp"
#include "ImageLoader.hpp"

class TrackModel {
public:
    TrackModel() {
        _trackInfos = new vector<TrackInfo *>();

    }

    void walk() {
        boost::filesystem::path path = boost::filesystem::current_path();
        boost::filesystem::recursive_directory_iterator itr(path);
        while (itr != boost::filesystem::recursive_directory_iterator()) {
            cout << itr->path().string() << endl;
            ++itr;
        }
    }


    void newTrack(string name, string dirname = "") {
//    Evt_add("type", func1);
        TrackInfo *trackInfo = new TrackInfo(name);
        trackInfo->idx = _trackInfos->size();
        _trackInfos->push_back(trackInfo);
        if (_trackInfo == nullptr)
            _trackInfo = trackInfo;
        TrackFrameInfo *pre = nullptr;
        if (dirname != "") {
            boost::filesystem::recursive_directory_iterator itr(dirname);
            while (itr != boost::filesystem::recursive_directory_iterator()) {
                if (itr->path().extension() == ".png") {
                    ImageInfo *imgInfo = ImageLoader()._().load(itr->path().string());
                    cout << typeid(this).name() << " load image: " << imgInfo->path << " " << imgInfo->width << " " <<
                    imgInfo->height << " id:" << imgInfo->id << endl;

                    TrackFrameInfo *trackFrameInfo = new TrackFrameInfo();
                    trackFrameInfo->imageInfo = imgInfo;
                    pre = trackFrameInfo->setPre(pre);
                    trackFrameInfo->setTrackInfoIdx(trackInfo->idx);
                    trackFrameInfo->setIdx(trackInfo->trackFrameInfos->size());
                    trackFrameInfo->setStartFrame(trackFrameInfo->getIdx() + 1);
                    trackFrameInfo->setHoldFrame(1);
                    trackInfo->append(trackFrameInfo);
                    if (!trackInfo->getHeadTrackFrameInfo())
                        trackInfo->setHead(trackFrameInfo);


                    ++itr;
                }
            }
        }
        else {//empty frame

        }
        cout << this << "trackInfo frame count:" << trackInfo->getFrameCount() << endl;
//        if (sizeof(trackInfo->trackFrameInfos) > sequencePlayback->endFrameIdx) {
//            sequencePlayback->endFrameIdx = sizeof(trackInfo->trackFrameInfos);
//        }
        Evt_dis(TrackModelEvent::NEW_TRACK, trackInfo);
    }

    void R2R(TrackFrameInfo *handleTrackFrame) {
        handleTrackFrame->setHoldFrame(handleTrackFrame->getHoldFrame() + 1);
        handleTrackFrame->foreach([](TrackFrameInfo *tfi) {
            tfi->setStartFrame(tfi->getStartFrame() + 1);
        }, handleTrackFrame);
    }

    void R2L(TrackFrameInfo *handleTrackFrame) {
        handleTrackFrame->setHoldFrame(handleTrackFrame->getHoldFrame() - 1);
        handleTrackFrame->foreach([](TrackFrameInfo *tfi) {
            tfi->setStartFrame(tfi->getStartFrame() - 1);
        }, handleTrackFrame);
    }

    void L2L(TrackFrameInfo *handleTrackFrame, TrackInfo *trackInfo) {
        //fixme
        if (handleTrackFrame->pre)
            removeTrackFrameInfo(handleTrackFrame->pre, trackInfo);
        handleTrackFrame->setStartFrame(handleTrackFrame->getStartFrame() - 1);
        handleTrackFrame->setHoldFrame(handleTrackFrame->getHoldFrame() + 1);
    }

    void L2R(TrackFrameInfo *handleTrackFrame, TrackInfo *trackInfo) {
        //fixme
        cout << typeid(this).name() << " L2R: " << handleTrackFrame->getIdx() << endl;
        if (handleTrackFrame->pre) {
            handleTrackFrame->pre->setHoldFrame(handleTrackFrame->pre->getHoldFrame() + 1);
        }
        if (handleTrackFrame->getHoldFrame() > 1) {
            handleTrackFrame->setStartFrame(handleTrackFrame->getStartFrame() - 1);
            handleTrackFrame->setHoldFrame(handleTrackFrame->getHoldFrame() - 1);
        }
        else {
            removeTrackFrameInfo(handleTrackFrame, trackInfo);
        }
    }


    int frameWidth = TIMELINE_TRACK_FRAME_MAX_WIDTH;
private:
    void removeTrackFrameInfo(TrackFrameInfo *tfi, TrackInfo *trackInfo) {
        vector<TrackFrameInfo *>::iterator i = trackInfo->trackFrameInfos->begin();
        while (i != trackInfo->trackFrameInfos->end()) {
            if (*i == tfi) {
                trackInfo->trackFrameInfos->erase(i);
                break;
            } else {
                i++;
            }
        }
        TrackFrameInfo *nextTfi = tfi->next;
        if (nextTfi)
            nextTfi->foreach([](TrackFrameInfo *tfiBackward) {
                tfiBackward->setIdx(tfiBackward->getIdx() - 1);
            }, nextTfi);
        tfi->remove();
    }

    TrackInfo *_trackInfo = nullptr;
    vector<TrackInfo *> *_trackInfos;
};