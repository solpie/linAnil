#pragma once
//
// Created by manoyuria on 2015/7/15.
//

#include <zconf.h>

#ifndef LINANIL_VSCOLOR_HPP
#define LINANIL_VSCOLOR_HPP

#endif //LINANIL_VSCOLOR_HPP

class VsColor {
public:
    VsColor() { }
    VsColor(int col) {
        setColor(col);
    }

    unsigned char r, g, b;

    void setColor(uInt col) {
        //todo
    }

    void setColor(int col) {
        //todo
        r = g = b = col;
    }
};