//
// Created by toramisu on 2015/7/27.
//

#pragma once

#include "BaseTrackInfo.hpp"
#include "vector"
class AudioTrackInfo : public BaseTrackInfo {
public:
    AudioTrackInfo(std::string n, int t);

    vector<float>* samples;
};

AudioTrackInfo::AudioTrackInfo(std::string n, int t) : BaseTrackInfo(n, t) {
    samples = new vector <float>;
}
