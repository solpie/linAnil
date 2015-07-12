#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_MOUSEEVENT_HPP
#define LINANIL_MOUSEEVENT_HPP

#endif //LINANIL_MOUSEEVENT_HPP

#include "BaseEvent.hpp"
class MouseEvent:public BaseEvent{
public:
    static constexpr const char *MOVE = "MOVE";
    static constexpr const char *DOWN = "DOWN";
    static constexpr const char *UP = "UP";

};