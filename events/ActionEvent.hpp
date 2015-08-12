//
// Created by toramisu on 2015/6/16.
//
#pragma once


#ifndef SEQTRUAN_ACTIONEVENT_H
#define SEQTRUAN_ACTIONEVENT_H

#endif //SEQTRUAN_ACTIONEVENT_H


class ActionEvent {
public:
    static constexpr const char *PROJECT_SAVE = "PROJECT_SAVE";
    //project not save yet
    static constexpr const char *PROJECT_CHANGED = "PROJECT_CHANGED";
    //edit image in external app
    static constexpr const char *Ext_EDIT = "Ext_EDIT";
};