//
// Created by toramisu on 2015/7/31.
//

#pragma once

#include "MenuItem.hpp"
#include "vector"

class PopupMenuInfo {
public:
    PopupMenuInfo(std::string title) {
        _title = title.c_str();
        _menuItems = new std::vector<MenuItem *>;

    }

    template<typename Observer>

    void addMenuItem(std::string text, Observer &&callback, void *data = nullptr) {
        MenuItem *mItem = new MenuItem(text, callback, data);
        _menuItems->push_back(mItem);
    }

    std::vector<MenuItem *> *getMenuItems() {
        return _menuItems;
    }

    std::string title() {
        return _title;
    }

    int width;
private:
    std::vector<MenuItem *> *_menuItems;
    std::string _title;
};
