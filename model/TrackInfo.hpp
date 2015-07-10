#pragma once
//
// Created by manoyuria on 2015/6/21.
//

#include "TrackFrameInfo.hpp"

#ifndef SEQTRUAN_TRACKINFO_HPP
#define SEQTRUAN_TRACKINFO_HPP

#endif //SEQTRUAN_TRACKINFO_HPP
using namespace std;

class TrackInfo {
public:
    TrackInfo(QString name) {
        this->name = name;
        trackFrameInfos = new vector<TrackFrameInfo *>();
    };
    QString name;
    vector<TrackFrameInfo *> *trackFrameInfos;
    int idx;

    int getEndFrame() {
        return _endFrame;
    }


    int getFrameCount() {
        int count = 0;
        for (TrackFrameInfo *trackFrameInfo:*trackFrameInfos) {
            count += trackFrameInfo->getHoldFrame();
        }
        return count;
    }


    int getCurTrackFrameIdx() { return _trackFrameIdx; };

    int getStartFrame() { return _startFrame; }

    void setStartFrame(int v) {
        _startFrame = v;
        _endFrame = v + getFrameCount();
    }

    double getOpacity() { return _opacity; }

    void setOpacity(double v) { _opacity = v; }

    bool visible = true;

    void append(TrackFrameInfo *a) {
        trackFrameInfos->push_back(a);
    }

    TrackFrameInfo *getHeadTrackFrameInfo() {
        return _head;
    }

    void setHead(TrackFrameInfo *tf) {
        _head = tf;
    }

protected:
    TrackFrameInfo *_head = nullptr;

    int _endFrame = 1;
    int _startFrame = 1;

    double _opacity = 1.0;
private:
    int _trackFrameIdx;

};