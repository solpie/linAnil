#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_VSOBJCONTAINER_HPP
#define LINANIL_VSOBJCONTAINER_HPP

#endif //LINANIL_VSOBJCONTAINER_HPP

#include "VsObj.hpp"
#include "vector"

class VsObjContainer : public VsObj {
public:
    VsObjContainer() : VsObj() {
        vsobjs = new vector<VsObj *>();
    }

    void addChild(VsObj *vsObj) {
        vsobjs->push_back(vsObj);
    }

    virtual void render() override {
        vector<VsObj *>::iterator child;
        for (child = vsobjs->begin(); child != vsobjs->end(); child++) {
            VsObj *c = *child;
            if (c->visible) {
                c->render();
            }
        }
    }

protected:
    vector<VsObj *> *vsobjs;
};

