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
#include <view/tools/WatchList.hpp>
#include "viewport/Viewport.hpp"
#include "KeyInput.hpp"
#include "menu/PopupMenu.hpp"
#include "dialog/OKDialog.hpp"
class Stage : public VsObjContainer {
public:
    Stage() {
        framesPlayback = new FramesPlayback(_proj);
        VS_CONTEXT.add(KeyEvent::DOWN, onKeyDown);
        VS_CONTEXT.add(KeyEvent::UP, onKeyUp);


        titleBar = new TitleBar();
        addChild(titleBar);

        vSplitter = new Splitter(Direction::Vertical);
        vSplitter->setY(titleBar->height);
        addChild(vSplitter);

        hSplitter = new Splitter(Direction::Horizontal);
        hSplitter->height = 720;
        vSplitter->addChild(hSplitter);

        viewport = new Viewport();
        hSplitter->addChild(viewport);

//        ColorWheel *colorWheel1 = new ColorWheel;
//        colorWheel1->setSize(300, 300);
        _watchList = new WatchList();
        VsObjContainer *toolShelf = new VsObjContainer();
        toolShelf->setSize(300, 300);
        toolShelf->addChild(_watchList);
        hSplitter->addChild(toolShelf);

        timeline = new Timeline();
        vSplitter->addChild(timeline);
//        vSplitter->swapChildRenderOrder();

        compTabs = new CompTabs();
        addChild(compTabs);

        //////popup layer
        popupLayer = new VsObjContainer();
        addChild(popupLayer);
        _popupMenu.init(popupLayer);
        _popupMenu.move(300, 300);
        _popupMenu.hide();
        /////// dialog
        _dialogOK.init(popupLayer);

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

    virtual void render() override {
        VS_RENDER_CHILDREN();
    }

    void setSize(int w, int h) override {
        titleBar->resize(w, h);
        vSplitter->setSize(w, h - titleBar->height-compTabs->height);
        compTabs->setSize(w, -1);
        compTabs->setY(h - compTabs->height);
        popupLayer->setSize(w, h);
    }

private:
    FramesPlayback *framesPlayback;
    Splitter *vSplitter;
    Splitter *hSplitter;

    TitleBar *titleBar;
    Timeline *timeline;
    Viewport *viewport;
    WatchList*_watchList;
    CompTabs *compTabs;
    //popup layer
    VsObjContainer* popupLayer;
};

