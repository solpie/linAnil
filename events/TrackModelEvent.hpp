#pragma once
//
// Created by manoyuria on 2015/6/18.
//


#include <model/TrackInfo.hpp>

#ifndef SEQTRUAN_TRACKMODELEVENT_H
#define SEQTRUAN_TRACKMODELEVENT_H

#endif //SEQTRUAN_TRACKMODELEVENT_H
class TrackModelEvent {
public:
    static constexpr const char *NEW_TRACK = "NEW_TRACK";
    static constexpr const char *LOAD_COMPLETE = "LOAD_COMPLETE";

    static constexpr const char *MOVE_TRACK = "MOVE_TRACK";
    static constexpr const char *SET_ZOOM_LEVEL = "SET_ZOOM_LEVEL";
    static constexpr const char *TRACK_FRAME_COUNT_CHANGED = "TRACK_FRAME_COUNT_CHANGED";

};