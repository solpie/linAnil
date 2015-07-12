#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_TIMELINE_HPP
#define LINANIL_TIMELINE_HPP

#endif //LINANIL_TIMELINE_HPP


#include "vs/Slider.hpp"

class Timeline : public VsObjContainer {
public:
    Timeline() {
        vSlider = new Slider();
        addChild(vSlider);
    }

    virtual void render() override;

private:
    Slider *vSlider;
};

void Timeline::render() {


    VsObjContainer::render();
}
