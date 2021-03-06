#pragma once
//
// Created by manoyuria on 2015/6/21.
//


#ifndef SEQTRUAN_TRACKFRAMEINFO_HPP
#define SEQTRUAN_TRACKFRAMEINFO_HPP

#endif //SEQTRUAN_TRACKFRAMEINFO_HPP

#include "utils/Linker.hpp"
#include "ImageLoader.hpp"

class TrackFrameInfo : public OneLinker<TrackFrameInfo> {
public:
    int getIdx() {
        return idx;
    }

    void setIdx(int i) {
        idx = i;
    }

    int getEndFrame() {
        return _endFrame;
    }

    int getStartFrame() const {
        return _startFrame;
    }


    void setStartFrame(int v) {
        _startFrame = v;
        _endFrame = _startFrame + _holdFrame - 1;

    }

    int getHoldFrame() const {
        return _holdFrame;
    }

    void setHoldFrame(int v) {
        _holdFrame = v;
        _endFrame = _startFrame + _holdFrame - 1;
    }



    void setTrackInfoIdx(int v) {
        _trackInfoIdx = v;
    }

    double opacity;//

    ImageInfo *imageInfo = nullptr;
    int x;
protected:
    int _trackInfoIdx;

    int _holdFrame = 0;
    int _endFrame = 1;
    int _startFrame = 1;

    int idx;

};

void dumpTrackFrameInfo(TrackFrameInfo *tfi) {
    cout<<"dumpTrackFrameInfo() idx:"<<tfi->getIdx()
            <<" start:"<<tfi->getStartFrame()
            <<" hold:"<<tfi->getHoldFrame()
            <<" end:"<<tfi->getEndFrame()<<endl;

}