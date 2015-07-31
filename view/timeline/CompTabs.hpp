//
// Created by toramisu on 2015/7/29.
//
#pragma once

#include "Sprite.hpp"
#include "model/ProjectInfo.hpp"

class CompTabs : public Sprite {
public:
    CompTabs(ProjectInfo *projInfo) {
        _projInfo = projInfo;
        height = 25;
    }

protected:
    virtual void onDraw() override {
        fillRect(_3RGB(47),gX(),gY(),width,height)
        fillRect(nvgRGB(THEME_COLOR_PANEL_BORDER_DARK), gX(), gY(), width, 1)
        fillRect(nvgRGB(THEME_COL_PANEL_BORDER_LIGHT), gX(), gY() + 1, width, 1)
        int px = TIMELINE_TRACK_PANEL_DEF_WIDTH;

        for (CompositionInfo *compInfo:*_projInfo->comps) {

            nvgFontFace(vg, "sans");
            nvgFontSize(vg, 14.0f);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, _3RGB(240));
            nvgText(vg, gX() + 5 + px, gY() + 5, compInfo->name.c_str(), nullptr);
            px += 90;
        }
        VS_RENDER_CHILDREN();
    }


private:
    ProjectInfo *_projInfo;
};
