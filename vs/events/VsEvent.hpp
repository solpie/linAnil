//
// Created by toramisu on 2015/7/14.
//
#pragma once
#ifndef LINANIL_VSEVENT_HPP
#define LINANIL_VSEVENT_HPP

#endif //LINANIL_VSEVENT_HPP
#include "BaseEvent.hpp"
class VsEvent:public BaseEvent{
public:
    static constexpr const char *INITED = "INITED";
    static constexpr const char *RENDER = "RENDER";
    static constexpr const char *RESIZE = "RESIZE";
    static constexpr const char *STAGE_MOUSE_UP = "STAGE_MOUSE_UP";
    static constexpr const char *STAGE_MOUSE_DOWN = "STAGE_MOUSE_DOWN";
};