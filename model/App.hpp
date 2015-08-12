//
// Created by manoyuria on 2015/6/18.
//
#pragma once
#ifndef SEQTRUAN_APP_H
#define SEQTRUAN_APP_H

#endif //SEQTRUAN_APP_H

#include <events/ActionEvent.hpp>
#include "utils/Singleton.hpp"
#include "CompositionInfo.hpp"
#include "ProjectInfo.hpp"
#include "vs/events/VsEvent.hpp"
#include "AppExternal.hpp"

class App : public Singleton<App> {
public:
    void start(int argc, char *argv[]) {
    }

    ProjectInfo *projInfo;

    void init() {
        projInfo = new ProjectInfo;
        Evt_add(ActionEvent::PROJECT_OPEN, onOpenProject);
        Evt_add(ActionEvent::PROJECT_SAVE, onSaveProject);
        Evt_add(ActionEvent::Ext_EDIT, onExtEdit);
        //default Comp
    }

    void onExtEdit(void *e) {
        AppExternal::editExternal(projInfo->curCompInfo->selectedTrackFrameInfo->imageInfo->path);
    }

    void onOpenProject(void *e) {
        string *path = get_paylaod(string);
        auto *openProj = new ProjectInfo();
        openProj->open(*path);


        projInfo = openProj;
    }

    void onSaveProject(void *e) {
        projInfo->saveToXml();
    }


    void test() {
        CompositionInfo *comp = projInfo->newComposition("comp1", 1280, 720, 24, 300);
//        App()._().curCompInfo->walk();
//        App()._().curCompInfo->newTrack("newTrack");
//        comp->newTrack("number", "D:/projects/linAnil/test/test30/");
//        comp->newTrack("curry", "D:/projects/linAnil/test/test10/");
//        comp->newTrack("audio track", "test/test.wav", TrackType::Audio);
        //todo comp2
//        CompositionInfo *comp2 = projInfo->newComposition("comp2", 1280, 720, 24, 300);
//        comp2->newTrack("number2", "D:/projects/linAnil/test/test30/");
    }

};

#define _app App()._()

#define _proj App()._().projInfo
