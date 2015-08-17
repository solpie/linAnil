//
// Created by toramisu on 2015/7/30.
//
#pragma once

#define DEF_FRAME_RATE 24 //project default framerate
enum ScaleMode : int {
    None = 1,
    Fit
};
struct ViewportConf {
    int scaleMode = ScaleMode::None;
};

struct Configs {
    ViewportConf viewport;
};
