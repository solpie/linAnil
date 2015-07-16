//
// Created by toramisu on 2015/7/13.
//

#ifndef LINANIL_CHECKBOX_HPP
#define LINANIL_CHECKBOX_HPP

#endif //LINANIL_CHECKBOX_HPP

#include "Sprite.hpp"

class CheckBox : public Sprite {
public:
    CheckBox() {
        add_event(MouseEvent::DOWN, onUp)
        setSize(14, 14);
    }

    bool isChecked = false;

protected:
    void onUp(MouseEvent *e) {
        isChecked = !isChecked;
    }

    virtual void onDraw() override {
        NVGcontext *vg = nvgContext;
        int r = 7;
        if (isChecked) {
            nvgBeginPath(vg);
            nvgCircle(vg, gX() + r, gY() + r, r);
            nvgFillColor(vg, nvgRGBA(182, 182, 182, 255));
            nvgFill(vg);
        }
        else {
//            nvgStrokeColor()
//            nvgFill(vg);
        }
        nvgBeginPath(vg);
        nvgCircle(vg, gX() + r, gY() + r, r);
        nvgStrokeColor(vg, nvgRGBA(52, 52, 52, 255));
        nvgStrokeWidth(vg, 1);
        nvgStroke(vg);

//        nvgSave(vg);

    }

};

