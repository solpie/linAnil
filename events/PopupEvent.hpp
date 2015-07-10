#pragma once
//
// Created by manoyuria on 2015/6/22.
//

#ifndef SEQTRUAN_POPUPEVENT_HPP
#define SEQTRUAN_POPUPEVENT_HPP

#endif //SEQTRUAN_POPUPEVENT_HPP

class PopupEvent {
public:
    map<QString, function<void()>> funcs;
    int posX;
    int posY;
    template <typename F>
    void add(QString name, F &&func) {
        funcs[name] = forward<function<void()>>(func);
    }
};