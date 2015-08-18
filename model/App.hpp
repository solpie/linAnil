//
// Created by manoyuria on 2015/6/18.
//
#pragma once

#include <events/ActionEvent.hpp>
#include <events/Evt.hpp>
#include <view/dialog/OKDialog.hpp>
#include "utils/Singleton.hpp"
#include "CompositionInfo.hpp"
#include "ProjectInfo.hpp"
#include "vs/events/VsEvent.hpp"
#include "TheMachine.hpp"
#include "Configs.hpp"

class App : public Singleton<App> {
public:
    void start(int argc, char *argv[]) {
    }

    Configs *conf;
    ProjectInfo *projInfo;
    TheMachine *tm;

    void init() {
        conf = new Configs;

        projInfo = new ProjectInfo;
        Evt_add(ActionEvent::PROJECT_TEST, onTestProject);
        Evt_add(ActionEvent::PROJECT_OPEN, onOpenProject);
        Evt_add(ActionEvent::PROJECT_SAVE, onSaveProject);
        //the machine
        tm = new TheMachine;
        Evt_add(ActionEvent::TM_EDIT, onExtEdit);
    }

    void onExtEdit(void *e) {
        tm->editExternal(projInfo->curCompInfo->selectedTrackFrameInfo->imageInfo);
    }

    void initAterStage() {
        //default comp
        projInfo->newComposition("comp1", 1280, 720, 24, 300);
    }


    void onOpenProject(void *e) {
        string *path = get_paylaod(string);
        auto *openProj = new ProjectInfo();
        openProj->open(*path);


        projInfo = openProj;
    }

    void onSaveProject(void *e) {
        projInfo->save("test.xml");
    }


    void onTestProject(void *e) {
//        App()._().curCompInfo->walk();
//        App()._().curCompInfo->newTrack("newTrack");
//        projInfo->curCompInfo->newTrack("number1", "D:/projects/linAnil/test/test30/");
//        projInfo->curCompInfo->newTrack("curry", "D:/projects/linAnil/test/test10/");
        projInfo->curCompInfo->newTrack("1pix", "D:/projects/linAnil/test/pix1/");
        projInfo->curCompInfo->newTrack("audio track", "test/test.wav", TrackType::Audio);


//        {//test new Track
//        ImageLoader::_().createPng("newFolder", "track1", 5, 100, 100);

//        }

        OKDialog::_().show();

        //comp2
//        CompositionInfo *comp2 = projInfo->newComposition("comp2", 1280, 720, 24, 300);
//        projInfo->curCompInfo = comp2;
//        comp2->newTrack("comp2number2", "D:/projects/linAnil/test/test30/");
    }

};

#define _app App()._()

#define _proj App()._().projInfo
#define _conf App()._().conf
