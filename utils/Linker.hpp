#pragma once
//
// Created by manoyuria on 2015/6/21.
//

#ifndef SEQTRUAN_TEST1_HPP
#define SEQTRUAN_TEST1_HPP

#endif //SEQTRUAN_TEST1_HPP

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

    void dispose() {

    }
};