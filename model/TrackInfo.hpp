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
    TrackInfo(string n) : BaseTrackInfo(n, TrackType::Image) {
        trackFrameInfos = new vector<TrackFrameInfo *>();
    };
    string name;
    //image folder path
    string path;
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

//    bool enable = true;

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

    TrackFrameInfo *newTrackFrameInfo(string filename, string path, TrackFrameInfo *pre) {
        ImageInfo *imgInfo = ImageLoader()._().load(path);
        imgInfo->filename = filename;;
//                        cout << typeid(this).name() << " setTrackInfo image: " << imgInfo->path << " " <<
//                        imgInfo->width <<
//                        " " <<
//                        imgInfo->height << " id:" << imgInfo->id << endl;

        TrackFrameInfo *trackFrameInfo = new TrackFrameInfo();
        trackFrameInfo->imageInfo = imgInfo;
        pre = trackFrameInfo->setPre(pre);
        trackFrameInfo->setTrackInfoIdx(idx);
        trackFrameInfo->setIdx(trackFrameInfos->size());
        trackFrameInfo->setStartFrame(trackFrameInfo->getIdx() + 1);
        trackFrameInfo->setHoldFrame(1);
        append(trackFrameInfo);
        if (!getHeadTrackFrameInfo())
            setHead(trackFrameInfo);
        return trackFrameInfo;
    }

protected:
    TrackFrameInfo *_head = nullptr;

    double _opacity = 1;
private:
    int _trackFrameIdx = -1;

};

