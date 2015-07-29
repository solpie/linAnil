//
// Created by manoyuria on 2015/6/18.
//
#pragma once
#ifndef SEQTRUAN_APP_H
#define SEQTRUAN_APP_H

#endif //SEQTRUAN_APP_H

#include "utils/Singleton.hpp"
#include "CompositionInfo.hpp"
#include "ProjectInfo.hpp"
#include "vs/events/VsEvent.hpp"

class App : public Singleton<App> {
public:
    void start(int argc, char *argv[]) {
    }

    ProjectInfo *projInfo;

    void init() {
        projInfo = new ProjectInfo;
        //default Comp
    }


    void test() {
        CompositionInfo *comp = projInfo->newComposition("comp1", 1280, 720, 24, 300);
//        App()._().curCompInfo->walk();
//        App()._().curCompInfo->newTrack("newTrack");
        comp->newTrack("number", "D:/projects/linAnil/test/test30/");
        comp->newTrack("audio track", "test/test.wav", TrackType::Audio);
        comp->newTrack("curry", "D:/projects/linAnil/test/test10/");
        //todo comp2
//        CompositionInfo *comp2 = projInfo->newComposition("comp2", 1280, 720, 24, 300);
//        comp2->newTrack("number2", "D:/projects/linAnil/test/test30/");
    }

};

#define _app App()._()

#define _proj App()._().projInfo
