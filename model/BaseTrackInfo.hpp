//
// Created by toramisu on 2015/7/27.
//


#ifndef LINANIL_BASETRACKINFO_HPP
#define LINANIL_BASETRACKINFO_HPP

#endif //LINANIL_BASETRACKINFO_HPP

#include <vs/VsColor.hpp>
#include <utils/Linker.hpp>
#include "string"

enum TrackType : int {
    Image = 1,
    Audio
};

class BaseTrackInfo : public OneLinker<BaseTrackInfo> {
public:
    BaseTrackInfo(std::string n, int t) {
        name = n;
        type = t;
    }

    bool visible = true;
    std::string name;
    int type;
    int idx;
    VsColor color;


    int getStartFrame() { return _startFrame; }

    void setStartFrame(int v) {
        _startFrame = v;
        _endFrame = v + getFrameCount();
    }

    virtual int getFrameCount() {
        return _lengthFrame;
    }

    int getEndFrame() {
        return _endFrame;
    }


protected:
    int _endFrame = 1;
    int _startFrame = 1;
    int _lengthFrame = 1;
};