#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_VSROOT_HPP
#define LINANIL_VSROOT_HPP

#endif //LINANIL_VSROOT_HPP

#include "vs/VsObjContainer.hpp"
#include "view/TrackArea.hpp"
#include "view/timeline/Timeline.hpp"
#include "vs/events/VsEvent.hpp"

class VsRoot : public VsObjContainer {
public:
    VsRoot() {
        for (int i = 0; i < 12; i++) {
            char file[128];
            snprintf(file, 128, "test/thumb/image%d.jpg", i + 1);
            images[i] = nvgCreateImage(VG_CONTEXT, file, 0);
            if (images[i] == 0) {
                printf("Could not load %s.\n", file);
//                return -1;
            }
        }

//        setX(500);
        timeline = new Timeline();
//        timeline->setY(width - 630);
        addChild(timeline);
        cout << this << "init root" << endl;
//        Evt_dis(VsEvent::INITED, nullptr)

    }

    virtual void render() override;

    void resize(int w, int h) {
        timeline->setY(h - 360);
        timeline->width = w;
        timeline->height = h;
    }

private:

    int images[12];
    Timeline *timeline;
};

void VsRoot::render() {
    drawThumbnails(VG_CONTEXT, 365, 30, 160, 300, images, 12, glfwGetTime());
    VsObjContainer::render();
}
