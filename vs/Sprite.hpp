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


    template<typename Observer>
    virtual void add(const string &event, Observer &&observer) override;

    virtual void render() override {
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
            }
        }
    }

    virtual void onDraw() { }

    virtual void onDrawEnd() { }

private:
    bool isInteractive;
};

template<typename Observer>
void Sprite::add(const string &event, Observer &&observer) {
    EventDispatcher::add(event, observer);
    isInteractive = (event == MouseEvent::MOVE || event == MouseEvent::DOWN || event == MouseEvent::UP)
}
