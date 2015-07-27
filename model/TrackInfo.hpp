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
        trackFrameInfos = new vector<TrackFrameInfo *>();
    };
    vector<TrackFrameInfo *> *trackFrameInfos;


    int getFrameCount() override {
        int count = 0;
        for (TrackFrameInfo *trackFrameInfo:*trackFrameInfos) {
            count += trackFrameInfo->getHoldFrame();
        }
        return count;
    }


    int getCurTrackFrameIdx() { return _trackFrameIdx; };


    double getOpacity() { return _opacity; }

    void setOpacity(double v) { _opacity = v; }


    void append(TrackFrameInfo *a) {
        trackFrameInfos->push_back(a);
    }

    TrackFrameInfo *getHeadTrackFrameInfo() {
        return _head;

    }

    void setHead(TrackFrameInfo *tf) {
        _head = tf;
    }

    bool isSelected = false;

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