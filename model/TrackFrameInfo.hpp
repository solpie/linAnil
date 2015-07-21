#pragma once
//
// Created by manoyuria on 2015/6/21.
//

//#include <QtGui/qimage.h>

#ifndef SEQTRUAN_TRACKFRAMEINFO_HPP
#define SEQTRUAN_TRACKFRAMEINFO_HPP

#endif //SEQTRUAN_TRACKFRAMEINFO_HPP

#include "utils/Linker.hpp"
#include "utils/Sh1tMacro.hpp"
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
        int dCount = v - _holdFrame;
        _holdFrame = v;
        _endFrame = _startFrame + _holdFrame - 1;
    }


    int getTrackInfoIdx() const {
        return _trackInfoIdx;
    }

    void setTrackInfoIdx(int v) {
        _trackInfoIdx = v;
    }


    void *getPayLoad() {
//        if (imageLoader->payLoad)
//            return imageLoader->payLoad;
//        return nullptr;
    }

//    ImageLoader *imageLoader = nullptr;

    void load(std::string path) {
//        if (!imageLoader) {
//            imageLoader = new ImageLoader();
//        }
//        imageLoader->load(path);
//        imageLoader->loadFunc = [] {
//            qDebug() << this << "loadFunc";;
//        };
    }

    double opacity;//


protected:
    int _trackInfoIdx;

    int _holdFrame = 0;
    int _endFrame = 1;
    int _startFrame = 1;

    int idx;

//    auto *payLoad;
//    PayLoad payLoad;
};