#pragma once
//
// Created by manoyuria on 2015/6/21.
//

#ifndef SEQTRUAN_SEQUENCEPLAYBACKEVENT_HPP
#define SEQTRUAN_SEQUENCEPLAYBACKEVENT_HPP

#endif //SEQTRUAN_SEQUENCEPLAYBACKEVENT_HPP

class SequencePlaybackEvent {
public:
    static constexpr const char *RENDER_FRAME = "RENDER_FRAME";
    static constexpr const char *STATE = "STATE";
    static constexpr const char *FRAME_RATE = "FRAME_RATE";
    int frameIdx;
    string state;
};