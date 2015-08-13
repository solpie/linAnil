//
// Created by toramisu on 2015/7/29.
//
#pragma once

#include "Sprite.hpp"
#include "model/ProjectInfo.hpp"

class CompTabs : public Sprite {
public:
    CompTabs() {
        height = 25;
        add_event(MouseEvent::UP, onUp)
    }

protected:
    int tabWidth = 90;
    int selectedX = TIMELINE_TRACK_PANEL_DEF_WIDTH;

    void onUp(void *e) {
        int idx = (mouseX() - TIMELINE_TRACK_PANEL_DEF_WIDTH) / tabWidth;
        _proj->showCompositionInfo(idx);
        selectedX = idx * tabWidth + TIMELINE_TRACK_PANEL_DEF_WIDTH;
    }

    virtual void onDraw() override {
        fillRect(_3RGB(47), gX(), gY(), width, height)
        fillRect(nvgRGB(THEME_COLOR_PANEL_BORDER_DARK), gX(), gY(), width, 1)
        fillRect(nvgRGB(THEME_COL_PANEL_BORDER_LIGHT), gX(), gY() + 1, width, 1)
        int px = TIMELINE_TRACK_PANEL_DEF_WIDTH;

        for (CompositionInfo *compInfo:*_proj->comps) {

            nvgFontFace(vg, "sans");
            nvgFontSize(vg, 14.0f);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, _3RGB(240));
            nvgText(vg, gX() + 5 + px, gY() + 5, compInfo->name.c_str(), nullptr);
            px += tabWidth;
        }

        fillRect(nvgRGB(THEME_COLOR_TITLEBAR_BOTTOM_BORDER), gX() + selectedX, gY()+height - 2, tabWidth, 2)


        VS_RENDER_CHILDREN();
    }


//private:
//    ProjectInfo *_projInfo;
};
