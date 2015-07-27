//
// Created by toramisu on 2015/7/27.
//

#pragma once

#include "BaseTrackInfo.hpp"

class AudioTrackInfo : public BaseTrackInfo {
public:
    AudioTrackInfo(std::string n, int t);
};

AudioTrackInfo::AudioTrackInfo(std::string n, int t) : BaseTrackInfo(n, t) {

}
