//
// Created by manoyuria on 2015/6/18.
//
#pragma once
#ifndef SEQTRUAN_APP_H
#define SEQTRUAN_APP_H

#endif //SEQTRUAN_APP_H

#include "UiRoot.hpp"
#include "utils/Singleton.hpp"
#include "TrackModel.hpp"
#include "vs/events/VsEvent.hpp"
class App : public Singleton<App> {
public:
    UiRoot *vsRoot = nullptr;

    void start(int argc, char *argv[]) {
        VS_CONTEXT.add(VsEvent::INITED, [this](void *e) { onInitContext(); });
    }

    TrackModel *trackModel;

    void init() {
        trackModel = new TrackModel();
        vsRoot = new UiRoot();
        VS_CONTEXT.add(VsEvent::RENDER, [this](void *e) { onRender(); });
        VS_CONTEXT.add(VsEvent::RESIZE, [this](void *e) { onResize(); });
    }

    void onInitContext() {
        init();
        initUI();
        test();
    }

    void onRender() {
        vsRoot->render();
//        test();
    }

    void onResize() {
        vsRoot->resize(VS_CONTEXT.width, VS_CONTEXT.height);
//        test();
    }

    void onInitRoot(void *e) {
//        test();
    }

    void initUI() {

    }

    void test() {
//        App()._().trackModel->walk();
        App()._().trackModel->newTrack("newTrack");
        App()._().trackModel->newTrack("newTrack2");
//        App()._().trackModel->newTrack("curry", "D:/projects/SeqTruanCpp/test/test30/");
//        App()._().trackModel->newTrack("curry", "D:/projects/SeqTruanCpp/test/test10/");
//        App()._().trackModel->audioPlayback->load("D:/projects/SeqTruanCpp/test/mp3.mp3");
//        App()._().trackModel->audioPlayback->play();
    }

};

#define _app App()._()
