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
        onUpdateFrameWidth();
    }

    virtual void onDraw() override {
        BaseTrack::drawBase();
        drawWaveForm();
        VS_RENDER_CHILDREN();
    }

    void onUpdateFrameWidth() {
        _audioTrackInfo->setSampleWidth(_sampleWidth, _proj->curCompInfo->frameWidth, _proj->curCompInfo->frameRate);
    }

private:
    void drawWaveForm() {
        int left = _scrollPosX + gX() + _trackLeft;

        //todo save to bitmap
//        drawWaveLineMix(_audioTrackInfo->mix);
        drawWaveLineSampleMix(_audioTrackInfo->sampleMix);
//        drawWaveLine(_audioTrackInfo->chR,false);

    }

    void drawWaveLine(vector<float> *chL, bool isLeft) {
        int left = _scrollPosX + gX() + _trackLeft;
        int py;
        if (isLeft)
            py = gY() + height / 4;
        else
            py = gY() + height * 3 / 4;
        nvgBeginPath(vg);
        nvgMoveTo(vg, left, py);
        for (int i = 0; i < chL->size(); i += _step) {
            nvgLineTo(vg, left + i / _step, py - (chL->at(i) * height / 2));
        }
        nvgLineTo(vg, left, py);
        nvgStrokeColor(vg, _3RGB(200));
        nvgStroke(vg);
    }

    void drawWaveLineMix(vector<float> *chL) {
        int left = _scrollPosX + gX() + _trackLeft;
        int py = gY() + height / 2;

        nvgBeginPath(vg);
        nvgMoveTo(vg, left, py);
        for (int i = 0; i < chL->size(); i += _step) {
            nvgLineTo(vg, left + i / _step, py - (chL->at(i) * height));
        }
        nvgStrokeColor(vg, _3RGB(200));
        nvgStroke(vg);
    }

    void drawWaveLineSampleMix(vector<float> *samples) {
        int left = _scrollPosX + gX() + _trackLeft;
        int py = gY() + height / 2;
        int sampleHeight;
        int sampleX;
        int showL = gX() + _trackLeft;
        int showR = gX() + width;
        int sw = _sampleWidth - 1;
        nvgSave(vg);
        for (int i = 0; i < samples->size(); ++i) {
            sampleX = left + i * _sampleWidth;
            if (sampleX >= showL) {
                if (sampleX > showR)
                    break;
                sampleHeight = (samples->at(i) * height);
                fillRect(_3RGB(200), sampleX, py - sampleHeight / 2, sw, sampleHeight)
            }
        }
        nvgRestore(vg);

    }

    int _step = 1800;
    int _sampleWidth = 10;
    AudioTrackInfo *_audioTrackInfo;

};