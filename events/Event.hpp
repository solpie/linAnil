//
// Created by manoyuria on 2015/6/16.
//
#pragma once
#ifndef SEQTRUAN_EVENT_H
#define SEQTRUAN_EVENT_H

#endif //SEQTRUAN_EVENT_H

#include "utils/Singleton.hpp"
#include <functional>
#include <map>
#include <vector>
#include <utility> // for forward
//#include "ActionEvent.hpp"
//#include "PlaybackEvent.hpp"
//#include "TrackModelEvent.hpp"
//#include "SequencePlaybackEvent.hpp"
//#include "PopupEvent.hpp"

#define Evt_add(type, func)  Evt()._().add(type, [this](void* e) { func(e); });
#define Evt_dis(type, param) Evt()._().dis(type, param);
using namespace std;


class Evt : public Singleton<Evt> {
public:
    Evt() = default;

//    Event<SequencePlaybackEvent> *seq;
//    Event<TrackModelEvent> *trackModelEvent;

//    void init() {
////        seq = new Event<SequencePlaybackEvent>();
////        trackModelEvent = new Event<TrackModelEvent>();
////        _map[typeid(SequencePlaybackEvent).name()] = seq;
//    }

//    map<string, void *> _map;

    template<typename Observer>
    void add(const string &event, Observer &&observer) {
        _observers[event].push_back(forward<function<void(void *)>>(observer));
    }

//    template<typename Observer>
//    void del(const string &event, Observer &&observer) {
//        if (_observers.find(event) != _observers.end())
//            for (const auto &obs : _observers.at(event)) {
//                if (obs == forward<function<void(void *)>>(observer)) {
//                    obs();
//                }
//            }
//    }

    void dis(const string &event, void *e = nullptr) const {
        if (_observers.find(event) != _observers.end())
            for (const auto &obs : _observers.at(event)) {
                if (e)
                    obs(e);
                else
                    obs(nullptr);
            }
    }


private:
    map<string, vector<function<void(void *)>>> _observers;

    // disallow copying and assigning
    Evt(const Evt &) = delete;

    Evt &operator=(const Evt &) = delete;


};
