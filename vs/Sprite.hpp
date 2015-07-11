#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_SPRITE_HPP
#define LINANIL_SPRITE_HPP

#endif //LINANIL_SPRITE_HPP

#include "VsObjContainer.hpp"

using namespace std;

class Sprite : public VsObjContainer {
public:
    Sprite() {

    }

    virtual void render() override {
        onDrawBegin();
        onDraw();
        onDrawEnd();
    }

    virtual void onDrawBegin() {
        int mx = VS_CONTEXT.cursor.x;
        int my = VS_CONTEXT.cursor.y;
        if (mx >= x() && my >= y() && mx <= x() + width && my <= y() + height) {
            cout << this << "hover" << endl;
        }
    }

    virtual void onDraw() { }

    virtual void onDrawEnd() { }

};
