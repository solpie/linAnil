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


//        addEvent(MouseEvent::UP, onUp);
        addEvent(MouseEvent::DOWN, onUp);
    };

    void onUp(void *e) {
        bool isSelected = !_trackInfo->isSelected;
        foreach([this](Track *t) { t->setSelected(false); });
        setSelected(isSelected);
    }

    void setSelected(bool v) {
        cout << this << " setSelected() " << _trackInfo->name << endl;
        _trackInfo->isSelected = v;
    }

    virtual void onDraw() override {
        NVGcontext *vg = nvgContext;
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        if (_trackInfo->isSelected)
            nvgFillColor(vg, nvgRGBA(colorSelect.r, colorSelect.g, colorSelect.b, 255));
        else
            nvgFillColor(vg, nvgRGBA(_trackInfo->color.r, _trackInfo->color.g, _trackInfo->color.b, 255));
        nvgFill(vg);
//        Sprite::onDraw();
        nvgBeginPath(vg);
        nvgStrokeColor(vg, nvgRGBA(0xff, 0x00, 0x00, 255));
//        nvgStrokeWidth(vg, 1);
        nvgMoveTo(vg, gX(), gY() + height);
        nvgLineTo(vg, gX() + width, gY() + height - 1);
        nvgStroke(vg);
        VsObjContainer::render();
    }

private:
    TrackInfo *_trackInfo;
    Slider *vSlider;
    CheckBox *trackVisibleBox;
};
