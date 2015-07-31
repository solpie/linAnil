#pragma once
//
// Created by manoyuria on 2015/6/21.
//

#include "TrackFrameInfo.hpp"

#ifndef SEQTRUAN_TRACKINFO_HPP
#define SEQTRUAN_TRACKINFO_HPP

#endif //SEQTRUAN_TRACKINFO_HPP

#include "vs/VsColor.hpp"
#include "BaseTrackInfo.hpp"

using namespace std;


class TrackInfo : public BaseTrackInfo {
public:
    TrackInfo(string n, int t) : BaseTrackInfo(n, t) {
        name = n;
        trackFrameInfos = new vector<TrackFrameInfo *>();
    };
    string name;
    vector<TrackFrameInfo *> *trackFrameInfos;
    int idx;
    VsColor color;

//    int getEndFrame() {
//        return _endFrame;
//    }


    int getFrameCount() override {
        int count = 0;
        for (TrackFrameInfo *trackFrameInfo:*trackFrameInfos) {
            count += trackFrameInfo->getHoldFrame();
        }
        return count;
    }


    virtual int getEndFrame() override {
        return getStartFrame() + trackFrameInfos->back()->getEndFrame()-1;
    }

    int getCurTrackFrameIdx() { return _trackFrameIdx; };

//    int getStartFrame() { return _startFrame; }
//
//    void setStartFrame(int v) {
//        _startFrame = v;
//        _endFrame = v + getFrameCount();
//    }

    double getOpacity() { return _opacity; }

    void setOpacity(double v) { _opacity = v; }

//    bool visible = true;

    void append(TrackFrameInfo *a) {
        trackFrameInfos->push_back(a);
    }

    TrackFrameInfo *getHeadTrackFrameInfo() {
        return _head;

    }

    void setHead(TrackFrameInfo *tf) {
        _head = tf;
    }


    int getCurrenTrackFrameIdx() {
        return _trackFrameIdx;
    }

    void setCurrenTrackFrameIdx(int v) {
        _trackFrameIdx = v;
    }

    ImageInfo *getCurrentImageInfo() {
        if (_trackFrameIdx > -1) {
            TrackFrameInfo *tfi = trackFrameInfos->at(_trackFrameIdx);
            if (tfi)
                return tfi->imageInfo;
        }
        return nullptr;
    }

protected:
    TrackFrameInfo *_head = nullptr;

    double _opacity = 1;
private:
    int _trackFrameIdx = -1;

};

