#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_SPRITE_HPP
#define LINANIL_SPRITE_HPP

#endif //LINANIL_SPRITE_HPP

#include <GLFW/glfw3.h>
#include <vs/events/SpriteEvent.hpp>
#include "VsObjContainer.hpp"

using namespace std;

#include "events/MouseEvent.hpp"

#define limit(value, min, max) if(value<min)value=min;else if(value>max)value=max;
enum Direction : int {
    Horizontal = 1,
    Vertical
};

class Sprite : public VsObjContainer {
public:
    Sprite() {
    }

    void onAdd(const string &event) override {
        if (!isInteractive)
            isInteractive = (
//                    event == MouseEvent::MOVE
                    event == MouseEvent::DOWN
                    || event == MouseEvent::ROLL_OVER
                    || event == MouseEvent::ROLL_OUT
                    || event == MouseEvent::UP);


        if (event == MouseEvent::ROLL_OVER) {
            _ignoreRollOver = false;
        }
        if (event == MouseEvent::ROLL_OUT) {
            _ignoreRollOut = false;
        }
    };

    virtual void render() override {
        VsObjContainer::updateZDepth();
        onDrawBegin();
        nvgSave(vg);
        onDraw();
        nvgRestore(vg);
        onDrawEnd();
    }


    bool mouseEnabled = true;
    bool isHover = false;
    bool isInteractive;

    int mouseX() {
        return VS_CONTEXT.cursor.x - gX();
    }

    int mouseY() {
        return VS_CONTEXT.cursor.y - gY();
    }

protected:
    virtual void onDrawBegin() {
        if (mouseEnabled && isInteractive && visible) {
            int mx = VS_CONTEXT.cursor.x;
            int my = VS_CONTEXT.cursor.y;
            bool isIn = false;
            if (isInRect(mx, my, gX(), gY(), width, height)) {
                isIn = true;
//                if (_mx != mx || _my != my) {
//                    _mx = mx;
//                    _my = my;
////                    VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::MOVE));
//                }
                if (VS_CONTEXT.enabeld) {
                    if (VS_CONTEXT.buttons == GLFW_MOUSE_BUTTON_1) {
                        if (VS_CONTEXT.action == GLFW_PRESS)
                            VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::DOWN));
                        else if (VS_CONTEXT.action == GLFW_RELEASE)
                            VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::UP));
                    }
                }
            }

            if (!isHover && isIn) {
                isHover = true;
                if (!_ignoreRollOver)
                    VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::ROLL_OVER));

            }
            else if (isHover && !isIn) {
                isHover = false;
                if (!_ignoreRollOut)
                    VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::ROLL_OUT));
            }
        }
    }


    virtual void onDraw() {
        disEvent(SpriteEvent::DRAW);
    }

    virtual void onDrawEnd() { }

private:
    bool _ignoreRollOut = true;
    bool _ignoreRollOver = true;
//    int _mx;
//    int _my;
};

