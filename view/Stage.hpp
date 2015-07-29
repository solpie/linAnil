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
#include <view/playback/FramesPlayback.hpp>
#include "viewport/Viewport.hpp"
#include "KeyInput.hpp"

class Stage : public VsObjContainer {
public:
    Stage() {
        framesPlayback = new FramesPlayback(_proj);
//        add_event_on_context(KeyEvent::DOWN,onKey)
        VS_CONTEXT.add(KeyEvent::DOWN, onKeyDown);
        VS_CONTEXT.add(KeyEvent::UP, onKeyUp);


        titleBar = new TitleBar();
        addChild(titleBar);

        vSplitter = new Splitter(Direction::Vertical);
        vSplitter->setY(titleBar->height);
        addChild(vSplitter);

        hSplitter = new Splitter(Direction::Horizontal);
        addChild(hSplitter);
        hSplitter->height = 720;
        vSplitter->addChild(hSplitter);

        viewport = new Viewport();
        hSplitter->addChild(viewport);

        ColorWheel *colorWheel1 = new ColorWheel;
        colorWheel1->setSize(300, 300);
        hSplitter->addChild(colorWheel1);

        timeline = new Timeline();
        vSplitter->addChild(timeline);

        compTabs = new CompTabs(_proj);
        addChild(compTabs);
        cout << typeid(this).name() << "init stage" << endl;
        VS_CONTEXT.add(VsEvent::RENDER, [this](void *e) { onRender(); });
        VS_CONTEXT.add(VsEvent::RESIZE, [this](void *e) { onResize(); });
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
//        viewport->resize(w, h);
//        hSplitter->setSize(w, -1);
//        timeline->setSize(w, h);
        vSplitter->setSize(w, h - titleBar->height-compTabs->height);

        compTabs->setSize(w, -1);
        compTabs->setY(h - compTabs->height);
    }

private:
    FramesPlayback *framesPlayback;
    Splitter *vSplitter;
    Splitter *hSplitter;

    TitleBar *titleBar;
    Timeline *timeline;
    Viewport *viewport;

    CompTabs *compTabs;
};

void Stage::render() {
//    drawThumbnails(VG_CONTEXT, 365, 30, 160, 300, images, 12, glfwGetTime());
    VsObjContainer::render();
}
