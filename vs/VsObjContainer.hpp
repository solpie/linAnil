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

    virtual void addChild(VsObj *vsObj) {
        vsObj->parent = this;
        vsobjs->push_back(vsObj);
    }

    void removeChild(VsObj *vsobj) {
        vsobj->parent = nullptr;
        vector<VsObj *>::iterator i = vsobjs->begin();
        while (i != vsobjs->end()) {
            if (*i == vsobj) {
                i = vsobjs->erase(i);
            } else {
                i++;
            }
        }
    }

    virtual void render() override {
        VsObj::updateZDepth();
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

