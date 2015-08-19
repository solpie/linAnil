//
// Created by toramisu on 2015/8/19.
//
#pragma once

#include <vs/Button.hpp>
#include <events/ActionEvent.hpp>
#include <events/Evt.hpp>

class WatchList : public Sprite {
public:
    WatchList() {
        width = 200;
        height = 350;

        _btnUpdate = new Button("update");
        _btnUpdate->move(5, 5);
        addChild(_btnUpdate);

        add_event_on(_btnUpdate, MouseEvent::UP, onUp)
    }


protected:
    Button *_btnUpdate;

    void onUp(void *e) {
        cout << typeid(this).name() << " update " << endl;
        Evt_ins.disEvent(ActionEvent::TM_UPDATE);
    }

    virtual void onDraw() override {
        fillRect(_3RGB(29), gX(), gY(), width, height)


        VS_RENDER_CHILDREN();
    }
};

