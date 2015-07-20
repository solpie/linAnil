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
#include "TitleBar.hpp"
#include <Splitter.hpp>
#include "viewport/Viewport.hpp"

class UiRoot : public VsObjContainer {
public:
    UiRoot() {
//        for (int i = 0; i < 12; i++) {
//            char file[128];
//            snprintf(file, 128, "test/thumb/image%d.jpg", i + 1);
//            images[i] = nvgCreateImage(VG_CONTEXT, file, 0);
//            if (images[i] == 0) {
//                printf("Could not load %s.\n", file);
////                return -1;
//            }
//        }



//        setX(500);
        titleBar = new TitleBar();
        addChild(titleBar);

        vSplitter = new Splitter(Direction::Vertical);
        vSplitter->setY(titleBar->height);
        addChild(vSplitter);
        viewport = new Viewport();
        viewport->move(0, 0);
        vSplitter->addChild(viewport);

        timeline = new Timeline();
        vSplitter->addChild(timeline);
        cout << this << "init root" << endl;
//        Evt_dis(VsEvent::INITED, nullptr)
        VS_CONTEXT.add(VsEvent::RENDER, [this](void *e) { onRender(); });
        VS_CONTEXT.add(VsEvent::RESIZE, [this](void *e) { onResize(); });

    }
    void onInitContext(){

    }
    void onResize() {
        resize(VS_CONTEXT.width, VS_CONTEXT.height);
    }
    void onRender() {
        render();
    }
    virtual void render() override;

    void resize(int w, int h) {
        titleBar->resize(w, h);
        viewport->resize(w, h);
//        timeline->setSize(w, h);
        vSplitter->setSize(w, h - titleBar->height);
    }

private:
    int images[12];
    Splitter *vSplitter;
    TitleBar *titleBar;
    Timeline *timeline;
    Viewport *viewport;
};

void UiRoot::render() {
//    drawThumbnails(VG_CONTEXT, 365, 30, 160, 300, images, 12, glfwGetTime());
    VsObjContainer::render();
}
