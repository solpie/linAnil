//
// Created by toramisu on 2015/7/13.
//
#pragma once

#include <vs/Sprite.hpp>
#include <view/Theme.hpp>

#ifndef LINANIL_TRACKTOOLBAR_HPP
#define LINANIL_TRACKTOOLBAR_HPP

#endif //LINANIL_TRACKTOOLBAR_HPP

class TrackToolBar : public VsObjContainer {
public:
    TrackToolBar() {
        height = 36;
        width = TIMELINE_TRACK_PANEL_DEF_WIDTH;
    }

    virtual void render() override {
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, _3RGB(20));
        nvgFill(vg);
        VS_RENDER_CHILDREN();
    }
};

