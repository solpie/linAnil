//
// Created by manoyuria on 2015/6/18.
//
#pragma once
#ifndef SEQTRUAN_APP_H
#define SEQTRUAN_APP_H

#endif //SEQTRUAN_APP_H

#include "utils/Singleton.hpp"
#include "model/TrackModel2.hpp"
#include "vs/events/VsEvent.hpp"

class App : public Singleton<App> {
public:

    void start(int argc, char *argv[]) {
        init();
        initUI();
    }

    TrackModel *trackModel;

    void init() {
        trackModel = new TrackModel();
        Evt_add(VsEvent::INITED, onInitRoot)
    }

    void onInitRoot(void *e) {
        test();
    }

    void initUI() {

    }

    void test() {
//        App()._().trackModel->walk();
        App()._().trackModel->newTrack("newTrack");
//        App()._().trackModel->newTrack("curry", "D:/projects/SeqTruanCpp/test/test30/");
//        App()._().trackModel->newTrack("curry", "D:/projects/SeqTruanCpp/test/test10/");
//        App()._().trackModel->audioPlayback->load("D:/projects/SeqTruanCpp/test/mp3.mp3");
//        App()._().trackModel->audioPlayback->play();
    }

};