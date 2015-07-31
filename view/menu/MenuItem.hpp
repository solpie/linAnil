//
// Created by toramisu on 2015/7/31.
//

#pragma once

#include "string"
#include "functional"

class MenuItem {
public:
    template<typename Observer>

    MenuItem(std::string text, Observer &&callback, void *data = nullptr) {
        this->text = text;
        this->data = data;
        _callback = forward<function<void(void *)>>(callback);

    }

    std::string text;

    void select() {
        _callback(nullptr);
    }
    void *data;
private:
    std::string _text;
     std::function<void(void *)> _callback;

};
