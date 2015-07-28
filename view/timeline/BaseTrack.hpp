//
// Created by toramisu on 2015/7/28.
//
#pragma once

#include <utils/Linker.hpp>
#include "Sprite.hpp"

class BaseTrack : public Sprite, public OneLinker<BaseTrack> {
public:
    BaseTrack(BaseTrackInfo *baseTrackInfo) {
        width = 1024;
        height = 55;
        _baseTrackInfo = baseTrackInfo;
        add_event(MouseEvent::DOWN, onDown);

    }

    void setColor(int r, int g, int b) {
        _baseTrackInfo->color.r = r;
        _baseTrackInfo->color.g = g;
        _baseTrackInfo->color.b = b;
        float h, s, v;
        RGBtoHSV(r, g, b, h, s, v);
        limit(v, v + 30, 255)
        float lightR, lightG, lightB;
        HSVtoRGB(h, s, v, lightR, lightG, lightB);
        selColor.r = lightR;
        selColor.g = lightG;
        selColor.b = lightB;
    }

    void drawBase() {
        if (parent && gY() < parent->gY())
            return;
        //bg
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        if (_baseTrackInfo->isSelected)
            nvgFillColor(vg, nvgRGBA(selColor.r, selColor.g, selColor.b, 255));
        else
            nvgFillColor(vg,
                         nvgRGBA(_baseTrackInfo->color.r, _baseTrackInfo->color.g, _baseTrackInfo->color.b, 255));
        nvgFill(vg);


        //track name
        nvgFontFace(vg, "sans");
        nvgFontSize(vg, 14.0f);
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgFillColor(vg, nvgRGBA(240, 240, 240, 192));
        nvgText(vg, gX() + 5, gY() + 5, _baseTrackInfo->name.c_str(), nullptr);

        //bottom border
        fillRect(_3RGB(52), gX(), gY() + height - 1, width, 1);
    }

    virtual void setSelected(bool v) {
        cout << this << " setSelected() " << _baseTrackInfo->name << endl;
        _baseTrackInfo->isSelected = v;
    }
    VsColor selColor;
protected:


    virtual void onDown(void *e) {
        VsEvent *vse = new VsEvent();
        vse->type = VsEvent::SELECTED;
        disEvent(vse);
        setSelected(true);
    }

    BaseTrackInfo *_baseTrackInfo;
};

