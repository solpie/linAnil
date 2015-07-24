#pragma once
#include "BaseEvent.hpp"

class KeyEvent : public BaseEvent {
public:
    static constexpr const char *DOWN = "DOWN";
    static constexpr const char *UP = "UP";
    int key;
};