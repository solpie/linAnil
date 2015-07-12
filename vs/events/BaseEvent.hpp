#pragma once
//
// Created by manoyuria on 2015/7/12.
//

#ifndef LINANIL_BASEEVENT_HPP
#define LINANIL_BASEEVENT_HPP

#endif //LINANIL_BASEEVENT_HPP

//using namespace std;
//template<class str>
class BaseEvent {
public:
    BaseEvent() { }

    static BaseEvent create(void* dispatcher,string t) {
        BaseEvent e;
        e.type = t;
        e.target = dispatcher;
        return e;
    }

    ~BaseEvent() {
//        delete target;
//        delete type;
    }

    void *target = nullptr;
    string type;
//    BaseEvent(const BaseEvent &) = delete;
//
//    BaseEvent &operator=(const BaseEvent &) = delete;
};