#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_SPRITE_HPP
#define LINANIL_SPRITE_HPP

#endif //LINANIL_SPRITE_HPP

#include "VsObjContainer.hpp"

using namespace std;

#include "events/MouseEvent.hpp"

class Sprite : public VsObjContainer {
public:
    Sprite() {
        mouseMove = [this] { disMove(); };
    }

    void disMove() {
        MouseEvent e;
//        e.target = this;
        disEvent(MouseEvent::MOVE, e);
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
        if (isInteractive) {

            int mx = VS_CONTEXT.cursor.x;
            int my = VS_CONTEXT.cursor.y;
            if (mx >= gX() && my >= gY() && mx <= gX() + width && my <= gY() + height) {
//                VS_CONTEXT.push(MouseEvent::MOVE, mouseMove);
                if (VS_CONTEXT.buttons == GLFW_MOUSE_BUTTON_1 && VS_CONTEXT.enabeld) {
//                    VS_CONTEXT.enabeld;
//                    VS_CONTEXT.push(MouseEvent::DOWN, [this] {
//                        disEvent(MouseEvent::create(MouseEvent::DOWN));
//                    });
                    VS_CONTEXT.pushUIEvent(MouseEvent::create(this, MouseEvent::DOWN));
                }
//
//                if (VS_CONTEXT.top) {
//                    if (zdepth >= ((VsObj *) (VS_CONTEXT.top))->zdepth) {
////                        VS_CONTEXT.top = this;
//                    }
//                }
//                else {
//                    VS_CONTEXT.push(MouseEvent::MOVE, mouseMove);
//
//                    VS_CONTEXT.top = this;
//                }

//                if(VS_CONTEXT.b)
            }
        }
    }

    function<void()> mouseMove;

    virtual void onDraw() { }

    virtual void onDrawEnd() {
        if (isInteractive && VS_CONTEXT.top == this) {
            if (VS_CONTEXT.buttons == GLFW_MOUSE_BUTTON_1 && VS_CONTEXT.enabeld) {
//                    VS_CONTEXT.enabeld;
                cout << this << "zdepth:" << zdepth << endl;
                VS_CONTEXT.top = this;
                VS_CONTEXT.enabeld = 0;
            }
        }

    }

private:
    bool isInteractive;
};

