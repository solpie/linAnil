#pragma once
//
// Created by manoyuria on 2015/7/10.
//

#ifndef LINANIL_INPUT_HPP
#define LINANIL_INPUT_HPP

#endif //LINANIL_INPUT_HPP

#include "vs/events/KeyEvent.hpp"

void onKeyDown(void *e) {
    KeyEvent *keyEvent = (KeyEvent *) e;
    if (keyEvent->key == GLFW_KEY_ESCAPE)
        VS_CONTEXT.close();
}

void onKeyUp(void *e) {
    KeyEvent *keyEvent = (KeyEvent *) e;

}