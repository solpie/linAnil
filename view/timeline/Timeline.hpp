#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_TIMELINE_HPP
#define LINANIL_TIMELINE_HPP

#endif //LINANIL_TIMELINE_HPP


#include "vs/VsObjContainer.hpp"

class Timeline : public VsObjContainer {
public:
    Timeline() {

    }

    virtual void render() override;
};

void Timeline::render() {
    VsObjContainer::render();

}
