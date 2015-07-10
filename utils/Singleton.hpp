#pragma once
//
// Created by toramisu on 2015/6/16.
//

#ifndef SEQTRUAN_SINGLETON_H
#define SEQTRUAN_SINGLETON_H

//#include "utility"
//class S {
//public:
//    static S &getInstance() {
//        static S instance; // Guaranteed to be destroyed.
//        // Instantiated on first use.
//        return instance;
//    }
//
//private:
//    S() { };                   // Constructor? (the {} brackets) are needed here.
//
//    // C++ 11
//    // =======
//    // We can use the better technique of deleting the methods
//    // we don't want.
//    S(S const &) = delete;
//
//    void operator=(S const &) = delete;
//
//};

template<typename T>
class Singleton {
public:
        static T &_() {
            static T instance;
            return instance;
        }


//private:
//    Singleton() {};                   // Constructor? (the {} brackets) are needed here.
//    // C++ 11
//    // =======
//    // We can use the better technique of deleting the methods
//    // we don't want.
//    Singleton(Singleton const&) = delete;
//
//    void operator=(Singleton const &) = delete;
};


#endif //SEQTRUAN_SINGLETON_H
