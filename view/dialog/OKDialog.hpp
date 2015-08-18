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
        }
    }

    void show() {
        if (isInit) {
            setX((parent->width - width) * .5);
            setX((parent->height - height) * .5);
            visible = true;
        }
    }

    void hide() {
        visible = false;
    }


protected:
    bool isInit = false;
};


#define _dialogOK OKDialog::_()