#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_VSROOT_HPP
#define LINANIL_VSROOT_HPP

#endif //LINANIL_VSROOT_HPP

#include "vs/VsObjContainer.hpp"
#include "view/timeline/Timeline.hpp"
#include "vs/events/VsEvent.hpp"
#include "TitleBar.hpp"
#include <Splitter.hpp>
#include "viewport/Viewport.hpp"
#include "Input.hpp"

class UiRoot : public VsObjContainer {
public:
    UiRoot() {
//        add_event_on_context(KeyEvent::DOWN,onKey)




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
        setSize(VS_CONTEXT.width, VS_CONTEXT.height);
    }
    void onRender() {
        render();
    }
    virtual void render() override;

    void setSize(int w, int h) override {
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
