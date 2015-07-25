#pragma once

#include "BaseEvent.hpp"

class KeyEvent : public BaseEvent {
public:
    ~KeyEvent() {
        cout << "destroy KeyEvent" << endl;
    }

    static constexpr const char *DOWN = "keyDown";
    static constexpr const char *UP = "keyUP";
    int key;
    bool isCtrl;
    bool isAlt;
    bool isShift;
    bool test = true;
};