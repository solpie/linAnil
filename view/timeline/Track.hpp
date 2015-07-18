//
// Created by toramisu on 2015/7/13.
//
#pragma once
#ifndef LINANIL_TRACK_HPP
#define LINANIL_TRACK_HPP

#endif //LINANIL_TRACK_HPP

#include <vs/Slider.hpp>
#include <vs/CheckBox.hpp>
#include "vs/Sprite.hpp"

class Track : public OneLinker<Track>, public Sprite {
public:
    Track(TrackInfo *trackInfo) {
        _trackInfo = trackInfo;
        width = 1024;
        height = 62;

        trackVisibleBox = new CheckBox();
        trackVisibleBox->isChecked = true;
        trackVisibleBox->setX(200);
        trackVisibleBox->setY(10);
        addChild(trackVisibleBox);

        vSlider = new Slider();
        vSlider->setValue(100);
        vSlider->setX(200);
        vSlider->setY(40);
        addChild(vSlider);

        scrollArea = new VsObjContainer();
        scrollArea->width = width;
        scrollArea->height = height;
        scrollArea->setX(TIMELINE_TRACK_PANEL_DEF_WIDTH);
        addChild(scrollArea);

        test = new CheckBox();
        scrollArea->addChild(test);
        add_event(MouseEvent::DOWN, onUp);
        setColor(99, 138, 20);
    };

    void onUp(void *e) {
        setSelected(true);
        disEvent(VsEvent::SELECTED, VsEvent());
    }

    void setSelected(bool v) {
        cout << this << " setSelected() " << _trackInfo->name << endl;
        _trackInfo->isSelected = v;
    }

    void setColor(int r, int g, int b) {
        _trackInfo->color.r = r;
        _trackInfo->color.g = g;
        _trackInfo->color.b = b;
        float h, s, v;
        RGBtoHSV(r, g, b, h, s, v);
        limit(v, v + 30, 255)
        float lightR, lightG, lightB;
        HSVtoRGB(h, s, v, lightR, lightG, lightB);
        selColor.r = lightR;
        selColor.g = lightG;
        selColor.b = lightB;
    }

    virtual void onDraw() override {
        {//bg
            nvgBeginPath(vg);
            nvgRect(vg, gX(), gY(), width, height);
            if (_trackInfo->isSelected)
                nvgFillColor(vg, nvgRGBA(selColor.r, selColor.g, selColor.b, 255));
            else
                nvgFillColor(vg, nvgRGBA(_trackInfo->color.r, _trackInfo->color.g, _trackInfo->color.b, 255));
            nvgFill(vg);
        }

        {//track name
            nvgFontFace(vg, "sans");
            nvgFontSize(vg, 14.0f);
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgFillColor(vg, nvgRGBA(240, 240, 240, 192));
            nvgText(vg, gX() + 5, gY() + 5, _trackInfo->name.c_str(), nullptr);
        }
        nvgBeginPath(vg);
        nvgFillColor(vg, nvgRGBA(52, 52, 52, 255));
        nvgRect(vg, gX(), gY() + height - 1, width, 1);
        nvgFill(vg);

        VsObjContainer::render();
    }

    void scrollX(int x) {
//        _scrollPosX = x;
        scrollArea->setX(-x+TIMELINE_TRACK_PANEL_DEF_WIDTH);
    }

    void resize(int w, int h) {
        width = w;
        height = h;
        scrollArea->width = w;
        scrollArea->height = h;
    }

private:
    CheckBox *test;
    VsObjContainer *scrollArea;
    int _scrollPosX;
    VsColor selColor;
    TrackInfo *_trackInfo;
    Slider *vSlider;
    CheckBox *trackVisibleBox;
};
