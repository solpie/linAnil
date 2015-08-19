#pragma once
//
// Created by manoyuria on 2015/7/12.
//

#ifndef LINANIL_BASEEVENT_HPP
#define LINANIL_BASEEVENT_HPP

#endif //LINANIL_BASEEVENT_HPP

using namespace std;

//template<class str>
class BaseEvent {
public:
    BaseEvent() { }

    BaseEvent(void *dispatcher, string t, void *p = nullptr) {
        this->target = dispatcher;
        this->type = t;
        payload = p;
    }

    static BaseEvent create(void *dispatcher, string t) {
        BaseEvent e;
        e.type = t;
        e.target = dispatcher;
        return e;
    }

    ~BaseEvent() {
//        delete target;
//        delete type;
    }

    void *payload = nullptr;

    void *target = nullptr;
    string type;
    bool isAccept = false;
};