//
// Created by toramisu on 2015/6/24.
//
#pragma once
#ifndef SEQTRUAN_OBSERVER_HPP
#define SEQTRUAN_OBSERVER_HPP

#endif //SEQTRUAN_OBSERVER_HPP
using namespace std;
class Obs {
public:
    Obs() = default;


    template<typename Observer>
    void add(const string &event, Observer &&observer) {
        _observers[event].push_back(std::forward<std::function<void(void *) >>(observer));
    }

    void dis(const string &event, void *e = nullptr) const {
        if (_observers.find(event) != _observers.end())
            for (const auto &obs : _observers.at(event)) {
                if (e)
                    obs(e);
                else
                    obs(nullptr);
            }
    }

    // disallow copying and assigning
    Obs(const Obs &) = delete;

    Obs &operator=(const Obs &) = delete;

private:
    std::map<string, std::vector<std::function<void(void *)>>> _observers;
};