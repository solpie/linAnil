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

class EventDispatcher {
public:

    template<typename Observer>
    void add(const string &type, Observer &&observer) {
        _funcs[type].push_back(forward<function<void(void *)>>(observer));
        onAdd(type);
    }
    virtual void onAdd(const string &event){
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
