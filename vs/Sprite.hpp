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
                MouseEvent e;
                disEvent(MouseEvent::MOVE, &e);
                if (VS_CONTEXT.buttons == GLFW_MOUSE_BUTTON_1 && VS_CONTEXT.enabeld) {
                    VS_CONTEXT.enabeld;
                    cout << this << "zdepth:" << zdepth << endl;
                    VS_CONTEXT.enabeld = 0;
                }
//                if(VS_CONTEXT.b)
            }
        }
    }

    virtual void onDraw() { }

    virtual void onDrawEnd() {
//        if (isInteractive) {
//            int mx = VS_CONTEXT.cursor.x;
//            int my = VS_CONTEXT.cursor.y;
//            if (mx >= gX() && my >= gY() && mx <= gX() + width && my <= gY() + height) {
//                MouseEvent e;
//                disEvent(MouseEvent::MOVE, &e);
//                if (VS_CONTEXT.buttons == GLFW_MOUSE_BUTTON_1 && VS_CONTEXT.enabeld) {
//                    VS_CONTEXT.enabeld;
//                    cout << this << "zdepth:" << zdepth << endl;
//                    VS_CONTEXT.enabeld = 0;
//                }
////                if(VS_CONTEXT.b)
//            }
//        }
    }

private:
    bool isInteractive;
};

