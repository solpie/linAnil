//
// Created by toramisu on 2015/6/16.
//
#pragma once


#ifndef SEQTRUAN_ACTIONEVENT_H
#define SEQTRUAN_ACTIONEVENT_H

#endif //SEQTRUAN_ACTIONEVENT_H

#include "events/BaseEvent.hpp"

class ActionEvent :public BaseEvent{
public:
    static constexpr const char *PROJECT_TEST = "PROJECT_TEST";
    static constexpr const char *PROJECT_OPEN = "PROJECT_OPEN";
    static constexpr const char *PROJECT_INITED = "PROJECT_INITED";
    static constexpr const char *PROJECT_SAVE = "PROJECT_SAVE";
    //project not save yet
    static constexpr const char *PROJECT_CHANGED = "PROJECT_CHANGED";
    static constexpr const char *PROJECT_NEW_COMP = "PROJECT_NEW_COMP";
    static constexpr const char *PROJECT_SHOW_COMP = "PROJECT_SHOW_COMP";
    //edit image in external app
    static constexpr const char *Ext_EDIT = "Ext_EDIT";

//    void* payload;
};