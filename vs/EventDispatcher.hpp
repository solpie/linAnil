#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#include <functional>
#include "map"

#ifndef LINANIL_VSEVENTDISPATCHER_HPP
#define LINANIL_VSEVENTDISPATCHER_HPP

#endif //LINANIL_VSEVENTDISPATCHER_HPP
using namespace std;

template<class VsEventDispatcher>
class EventDispatcher {
public:
    template<typename Observer>
    void addEvent(const string &event, Observer &&func) {
        _funcs[event] = forward<function<void(void *)>>(func);
    }

    void disEvent(const string event, void *e = nullptr) {
        if (_funcs.find(event) != _funcs.end())
            _funcs.at(event)(e);
    }

protected:
    map<string, function<void(void *)>> _funcs;
};
