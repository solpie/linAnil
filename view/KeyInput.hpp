#pragma once
//
// Created by manoyuria on 2015/7/10.
//

#ifndef LINANIL_INPUT_HPP
#define LINANIL_INPUT_HPP

#endif //LINANIL_INPUT_HPP

#include "vs/events/KeyEvent.hpp"
#include "events/PlaybackEvent.hpp"

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
}

void onKeyUp(void *e) {
    KeyEvent *keyEvent = (KeyEvent *) e;

}