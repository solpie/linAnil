//
// Created by toramisu on 2015/6/16.
//
#pragma once


#ifndef SEQTRUAN_ACTIONEVENT_H
#define SEQTRUAN_ACTIONEVENT_H

#endif //SEQTRUAN_ACTIONEVENT_H


class ActionEvent {
public:
    static constexpr const char *TOGGLE_PLAY = "TOGGLE_PLAY";
    static constexpr const char *UPDATE_CURSOR = "UPDATE_CURSOR";

    static constexpr const char *POPUP_MENU = "POPUP_MENU";
    static constexpr const char *SCROLL_TIMELINE_HBAR = "SCROLL_TIMELINE_HBAR";
    int param1;
};