#pragma once
//
// Created by manoyuria on 2015/6/19.
//
class PlaybackEvent{
public:
    static constexpr const char *PLAY = "PLAY";
    static constexpr const char *PAUSE = "PAUSE";
    static constexpr const char *STOP = "STOP";
    static constexpr const char *TOGGLE = "togglePlayPause";
    static constexpr const char *FORWARD = "frame go forward";
    static constexpr const char *BACKWARD = "frame go backward";
};