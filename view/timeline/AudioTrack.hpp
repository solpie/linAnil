//
// Created by toramisu on 2015/7/27.
//

#ifndef LINANIL_AUDIOTRACK_HPP
#define LINANIL_AUDIOTRACK_HPP

#endif //LINANIL_AUDIOTRACK_HPP

#include "BaseTrack.hpp"

class AudioTrack : public BaseTrack {
public:
    AudioTrack(AudioTrackInfo *audioTrackInfo) : BaseTrack((BaseTrackInfo *) audioTrackInfo) {
        _audioTrackInfo = audioTrackInfo;
        setColor(99, 138, 20);

    }

    virtual void onDraw() override {
        BaseTrack::drawBase();
        drawWaveForm();
        VS_RENDER_CHILDREN();
    }

private:
    void drawWaveForm() {

    }

    AudioTrackInfo *_audioTrackInfo;

};