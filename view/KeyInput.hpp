#pragma once
//
// Created by manoyuria on 2015/7/10.
//

#include "vs/events/KeyEvent.hpp"
#include "events/PlaybackEvent.hpp"
#include "events/ActionEvent.hpp"

void onKeyDown(void *e) {
    KeyEvent *keyEvent = (KeyEvent *) e;
    if (keyEvent->key == GLFW_KEY_F4 && keyEvent->isAlt)
        VS_CONTEXT.close();
        /*********************************************************
        *   transport
        * *******************************************************/
    else if (keyEvent->key == GLFW_KEY_ESCAPE) {
        Evt_ins.disEvent(PlaybackEvent::STOP);
    }
    else if (keyEvent->key == GLFW_KEY_SPACE) {
        Evt_ins.disEvent(PlaybackEvent::TOGGLE);
    }
    else if (keyEvent->key == GLFW_KEY_F) {
        Evt_ins.disEvent(PlaybackEvent::FORWARD);
    }
    else if (keyEvent->key == GLFW_KEY_D) {
        Evt_ins.disEvent(PlaybackEvent::BACKWARD);
    }
        /*********************************************************
         * The machine
         * *******************************************************/

    else if (keyEvent->key == GLFW_KEY_ENTER) {
        Evt_ins.disEvent(ActionEvent::TM_EDIT);
    }
    else if (keyEvent->key == GLFW_KEY_F5) {
        Evt_ins.disEvent(ActionEvent::TM_UPDATE);
    }
        /*********************************************************
         *  project open save
         * *******************************************************/
    else if (keyEvent->key == GLFW_KEY_T && keyEvent->isCtrl) {
        Evt_ins.disEvent(ActionEvent::PROJECT_TEST);
    }
    else if (keyEvent->key == GLFW_KEY_S && keyEvent->isCtrl) {
        Evt_ins.disEvent(ActionEvent::PROJECT_SAVE);
    }
    else if (keyEvent->key == GLFW_KEY_O && keyEvent->isCtrl) {
        auto *e = new ActionEvent();
        e->type = ActionEvent::PROJECT_OPEN;
        string path = "test.xml";
        e->payload = &path;
        Evt_ins.disEvent(e);
    }
}

void onKeyUp(void *e) {
    KeyEvent *keyEvent = (KeyEvent *) e;

}