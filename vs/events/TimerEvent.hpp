#pragma once
//
// Created by manoyuria on 2015/7/25.
//

#ifndef LINANIL_TIMEREVENT_HPP
#define LINANIL_TIMEREVENT_HPP

#endif //LINANIL_TIMEREVENT_HPP

#include "BaseEvent.hpp"

class TimerEvent : public BaseEvent {
public:
    static constexpr const char *TICK = "TICK";
    static constexpr const char *TIMER_COMPLETE = "timerComplete";
};