#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_VSCONTEXT_HPP
#define LINANIL_VSCONTEXT_HPP

#endif //LINANIL_VSCONTEXT_HPP

#include <c++/4.9.2/exception>
#include "nanovg/nanovg.h"

#define VS_CONTEXT  VsContext::_().getContext()
using namespace std;

template<typename T>
class S {
public:
    static T &_() {
        static T instance;
        return instance;
    }

};

class VsContext : public S<VsContext> {
public:


    void init(NVGcontext *vg) {
        nvgContext = vg;
    }

    NVGcontext *getContext() {
        if (nvgContext)
            return nvgContext;
        else {
            string e = "call init() first!";
            cout<<this<<e<<endl;
            throw runtime_error(e.c_str());
        }
    }

protected:
    NVGcontext *nvgContext = nullptr;
};