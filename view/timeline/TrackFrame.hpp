//
// Created by toramisu on 2015/7/21.
//
#include <model/TrackFrameInfo.hpp>
#include "Sprite.hpp"

class TrackFrame : public VsObjContainer {
public:
    TrackFrame(TrackFrameInfo *trackFrameInfo) {
        _trackFrameInfo = trackFrameInfo;

        _leftButton = new Sprite();
        addChild(_leftButton);

        _rightButton = new Sprite();
        addChild(_rightButton);
    }


    void render() override {

    }

private:
    TrackFrameInfo *_trackFrameInfo;
    Sprite *_leftButton;
    Sprite *_rightButton;
};