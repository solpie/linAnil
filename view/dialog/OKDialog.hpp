//
// Created by toramisu on 2015/8/18.
//
#pragma once

#include <utils/Singleton.hpp>
#include "BaseDialog.hpp"


class OKDialog : public BaseDialog, public Singleton<OKDialog> {
public:
    void init(VsObjContainer *parent) {
        if (!isInit) {
            isInit = true;
            parent->addChild(this);
            visible = false;
            setTitle("comfirm?");
            setText("are you ok?");


            _btnOk = new Button("OK");
            _btnOk->move(30, 140);
            addChild(_btnOk);

            _btnCancel = new Button("Cancel");
            _btnCancel->move(300, 140);
            addChild(_btnCancel);

            add_event_on(_btnOk, MouseEvent::UP, onUpOk);
            add_event_on(_btnCancel, MouseEvent::UP, onUpCancel);
        }
    }

    void onUpCancel(void *e) {
        this->hide();
        BaseEvent se(this, VsEvent::SELECTED);
        se.payload = (void *) false;
        disEvent(&se);
    }

    void onUpOk(void *e) {
        this->hide();
        BaseEvent se(this, VsEvent::SELECTED);
        se.payload = (void *) true;
        disEvent(&se);
    }

    void show(int x = 0, int y = 0) {
        if (isInit) {
            if (!x)
                x = (VS_CONTEXT.width - width) * .5;
            if (!y)
                y = (VS_CONTEXT.height - height) * .5;
            move(x, y);
            visible = true;
        }
    }

    void hide() {
        visible = false;
    }


protected:
    Button *_btnOk;
    Button *_btnCancel;
    bool isInit = false;
};


#define _dialogOK OKDialog::_()