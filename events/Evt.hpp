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
//todo event delete
#define Evt_dis(type, param) Evt()._().disEvent(type, param);
#define Evt_ins Evt()._()
using namespace std;

#include "vs/events/EventDispatcher.hpp"

class Evt : public EventDispatcher, public Singleton<Evt> {
};
