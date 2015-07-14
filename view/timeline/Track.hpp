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
    Track() {
        width = 1024;
        height = 62;

        trackVisibleBox = new CheckBox();
        trackVisibleBox->isChecked = true;
        trackVisibleBox->setX(200);
        trackVisibleBox->setY(10);
        addChild(trackVisibleBox);

        vSlider = new Slider();
        vSlider->setX(200);
        vSlider->setY(40);
        addChild(vSlider);
    };


    virtual void onDraw() override {
        NVGcontext *vg = nvgContext;
        nvgBeginPath(vg);
        nvgRect(vg, gX(), gY(), width, height);
        nvgFillColor(vg, nvgRGBA(99, 99, 99, 255));
        nvgFill(vg);
//        Sprite::onDraw();
        VsObjContainer::render();
    }

private:
    Slider *vSlider;
    CheckBox *trackVisibleBox;
};
