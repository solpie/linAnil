//
// Created by toramisu on 2015/7/31.
//

#pragma once

#include "string"
#include "functional"

class MenuItem {
public:
    MenuItem(std::string text, std::function<void(void *)> *callback, void *data = nullptr) {
        this->text = text;
        this->data = data;
        _callback = callback;
        _c_str = text.c_str();
    }

    std::string text;

    const char *c_str() {
        _c_str;
    }

    void *data;
private:
    const char *_c_str;
     std::function<void(void *)> *_callback;

};
