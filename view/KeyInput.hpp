#pragma once
//
// Created by manoyuria on 2015/7/10.
//

#ifndef LINANIL_INPUT_HPP
#define LINANIL_INPUT_HPP

#endif //LINANIL_INPUT_HPP

#include "vs/events/KeyEvent.hpp"
#include "events/PlaybackEvent.hpp"
#include "events/ActionEvent.hpp"

void onKeyDown(void *e) {
    KeyEvent *keyEvent = (KeyEvent *) e;
    if (keyEvent->key == GLFW_KEY_F4 && keyEvent->isAlt)
        VS_CONTEXT.close();
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
    else if (keyEvent->key == GLFW_KEY_ENTER) {
        Evt_ins.disEvent(ActionEvent::Ext_EDIT);
    }
    else if (keyEvent->key == GLFW_KEY_S && keyEvent->isCtrl) {
        Evt_ins.disEvent(ActionEvent::PROJECT_SAVE);
    }
    else if (keyEvent->key == GLFW_KEY_O && keyEvent->isCtrl) {
        auto *e = new ActionEvent();
        e->type = ActionEvent::PROJECT_OPEN;
        string path = "c:\\test.xml";
        e->payload = &path;
        Evt_ins.disEvent(e);
    }
}

void onKeyUp(void *e) {
    KeyEvent *keyEvent = (KeyEvent *) e;

}