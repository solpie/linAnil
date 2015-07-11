#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#include <functional>
#include "map"

#ifndef LINANIL_VSEVENTDISPATCHER_HPP
#define LINANIL_VSEVENTDISPATCHER_HPP

#endif //LINANIL_VSEVENTDISPATCHER_HPP
#define addEvent(type,func) add(type, [this](void* e) { func(e); });
using namespace std;

template<class VsEventDispatcher>
class EventDispatcher {
public:

    virtual template<typename Observer>
    void add(const string &event, Observer &&observer) {
        _funcs[event].push_back(forward<function<void(void *)>>(observer));
    }

    void disEvent(const string event, void *e = nullptr) const {
        if (_funcs.find(event) != _funcs.end())
            for (const auto &obs : _funcs.at(event)) {
                if (e)
                    obs(e);
                else
                    obs(nullptr);
            }
    }

protected:
    map<string, vector<function<void(void *)>>> _funcs;

};
