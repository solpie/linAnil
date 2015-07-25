#pragma once
//
// Created by manoyuria on 2015/6/21.
//

#ifndef LINANIL_UTILS_LINKER_HPP
#define LINANIL_UTILS_LINKER_HPP

#endif //LINANIL_UTILS_LINKER_HPP

template<typename CLS>
class OneLinker {
public:
    CLS *pre = nullptr;
    CLS *next = nullptr;

    CLS *setPre(CLS *pre) {
        if (pre) {
            this->pre = pre;
            pre->next = this;
        }
        return this;
    }

    CLS *remove() {
        if (this->pre && this->next) {
            this->pre->next = this->next;
            this->next->pre = this->pre;
        }
        else {
            if (this->next) {
                this->next->pre = nullptr;
            }
            else if (this->pre) {
                this->pre->next = nullptr;
            }
        }
        this->next = nullptr;
        this->pre = nullptr;
        return this;
    }

    CLS *getTail() {
        if (next)
            return next->getTail();
        else
            return this;
    }

    CLS *getHead() {
        if (pre)
            return pre->getHead();
        else
            return this;
    }

    template<typename func>

    void foreach(func &&f) {
        foreach(f, getHead());
    }

    template<typename func>

    void foreach(func &&f, CLS *from) {
        CLS *h = from;
        while (h) {
            f(h);
            h = h->next;
        }
    }

    void dispose() {

    }
};