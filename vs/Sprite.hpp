#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_SPRITE_HPP
#define LINANIL_SPRITE_HPP

#endif //LINANIL_SPRITE_HPP

#include <GLFW/glfw3.h>
#include "VsObjContainer.hpp"

using namespace std;

#include "events/MouseEvent.hpp"

class Sprite : public VsObjContainer {
public:
    Sprite() {
    }

    void onAdd(const string &event) override {
        isInteractive = (event == MouseEvent::MOVE || event == MouseEvent::DOWN || event == MouseEvent::UP);
    };

    virtual void render() override {
        VsObjContainer::updateZDepth();
        onDrawBegin();
        onDraw();
        onDrawEnd();
    }

    virtual void onDrawBegin() {
        if (mouseEnabled&&isInteractive) {
            int mx = VS_CONTEXT.cursor.x;
            int my = VS_CONTEXT.cursor.y;
            bool isIn = false;
            if (mx >= gX() && my >= gY() && mx <= gX() + width && my <= gY() + height) {
                isIn = true;
                if (_mx != mx || _my != my) {
                    _mx = mx;
                    _my = my;
                    VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::MOVE));
                }
                if (VS_CONTEXT.enabeld) {
                    if (VS_CONTEXT.buttons == GLFW_MOUSE_BUTTON_1) {
                        if (VS_CONTEXT.action == GLFW_PRESS)
                            VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::DOWN));
                        else if (VS_CONTEXT.action == GLFW_RELEASE)
                            VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::UP));
                    }
                }
            }

            if (!_isHover && isIn) {
                _isHover = true;
                VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::ROLL_OVER));

            }
            else if (_isHover && !isIn) {
                _isHover = false;
                VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::ROLL_OUT));
            }
        }
    }


    virtual void onDraw() { }

    virtual void onDrawEnd() {

    }

    bool mouseEnabled = true;
private:

    bool _isHover = false;
    int _mx;
    int _my;
    bool isInteractive;
};

