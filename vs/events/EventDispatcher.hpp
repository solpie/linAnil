#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#include <functional>
#include "map"
#include "vector"

#ifndef LINANIL_VSEVENTDISPATCHER_HPP
#define LINANIL_VSEVENTDISPATCHER_HPP

#endif //LINANIL_VSEVENTDISPATCHER_HPP
#define add_event(type, func) add(type, [this](void* e) { func(e); });
#define add_event_on(obj, type, func) obj->add_event(type,func);
#define get_dispatcher(ttype) (ttype *) ((BaseEvent *) e)->target
#define get_paylaod(ttype) (ttype *) ((BaseEvent *) e)->payload

#include "BaseEvent.hpp"

using namespace std;

class EventDispatcher {
public:

    template<typename Observer>
    void add(const string &type, Observer &&observer) {
        _funcs[type].push_back(forward<function<void(void *)>>(observer));
        onAdd(type);
    }

    virtual void onAdd(const string &event) {
    }


    void disEvent(BaseEvent* e) {
        disEvent(e->type, e);
    }

    void disEvent(const string event, BaseEvent* e) {
        if (_funcs.find(event) != _funcs.end())
            for (const auto &obs : _funcs.at(event)) {
                e->target = this;
                obs(e);
            }
    }

    void disEvent(const string event) {
        if (_funcs.find(event) != _funcs.end())
            for (const auto &obs : _funcs.at(event)) {
                obs(nullptr);
            }
    }

protected:
    map<string, vector<function<void(void *)>>> _funcs;
};
