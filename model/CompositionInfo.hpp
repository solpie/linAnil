//
// Created by toramisu on 2015/7/10.
//
#pragma once


#include "TrackInfo.hpp"
#include "vector"
#include "boost/filesystem.hpp"

#include "iostream"
#include "windows.h"

using namespace boost;

#include <stack>
#include <view/Theme.hpp>
#include "events/TrackModelEvent.hpp"
#include "ImageLoader.hpp"
#include "AudioTrackInfo.hpp"
#include "events/EventDispatcher.hpp"
class CompositionInfo :public EventDispatcher{
public:
    CompositionInfo() {
        _trackInfos = new vector<BaseTrackInfo *>();
        _trackFrameInfotoRemoves = new vector<TrackFrameInfo *>();
        //default track
//        _trackInfos->push_back(newTrackInfo("track"));
    }
    int idx;
    int width;
    int height;
    int frameRate;
    string name;
    int durationFrame;
    int frameWidth = TIMELINE_TRACK_FRAME_MAX_WIDTH;
    TrackFrameInfo *selectedTrackFrameInfo;

    void walk() {
        boost::filesystem::path path = boost::filesystem::current_path();
        boost::filesystem::recursive_directory_iterator itr(path);
        while (itr != boost::filesystem::recursive_directory_iterator()) {
            cout << itr->path().string() << endl;
            ++itr;
        }
    }


    TrackInfo *newTrackInfo(string name, string dirname = "") {
        TrackInfo *trackInfo = new TrackInfo(name);
        trackInfo->idx = _trackInfos->size();
        _trackInfos->push_back(trackInfo);
        if (_trackInfoHead == nullptr)
            _trackInfoHead = trackInfo;
        trackInfo->path = dirname;

        return trackInfo;

    }

    void newTrack(string name, string dirname = "", int type = TrackType::Image) {
        if (type == TrackType::Image) {
            TrackInfo *trackInfo = newTrackInfo(name, dirname);

            TrackFrameInfo *pre = nullptr;
            if (dirname != "") {
                boost::filesystem::recursive_directory_iterator itr(dirname);
                while (itr != boost::filesystem::recursive_directory_iterator()) {
                    if (itr->path().extension() == ".png") {
                        trackInfo->newTrackFrameInfo(itr->path().filename().string(), itr->path().string());
                        ++itr;
                    }
                }
            }
            else {//empty frame

            }

            cout << this << "trackInfo frame count:" << trackInfo->getFrameCount() << endl;
            updateContentEndFrame();

            BaseEvent *e = new BaseEvent;
            e->payload = trackInfo;
            e->type = TrackModelEvent::NEW_TRACK;
            disEvent(e);

        }
        else if (type == TrackType::Audio) {
            AudioTrackInfo *audioTrackInfo = new AudioTrackInfo(name);
            _trackInfos->push_back(audioTrackInfo);
            audioTrackInfo->load(dirname);

            BaseEvent *e = new BaseEvent;
            e->payload = audioTrackInfo;
            e->type = TrackModelEvent::NEW_TRACK;
            disEvent(e);
        }
    }

    void R2R(TrackFrameInfo *handleTrackFrame) {
        handleTrackFrame->setHoldFrame(handleTrackFrame->getHoldFrame() + 1);
        handleTrackFrame->foreach([](TrackFrameInfo *tfi) {
            tfi->setStartFrame(tfi->getStartFrame() + 1);
        }, handleTrackFrame->next);
        updateContentEndFrame();
    }

    void R2L(TrackFrameInfo *handleTrackFrame) {
        handleTrackFrame->setHoldFrame(handleTrackFrame->getHoldFrame() - 1);
        handleTrackFrame->foreach([](TrackFrameInfo *tfi) {
            tfi->setStartFrame(tfi->getStartFrame() - 1);
        }, handleTrackFrame->next);
        updateContentEndFrame();
//        dumpTrackFrameIdx(trackInfo);
    }

    void L2L(TrackFrameInfo *handleTrackFrame, TrackInfo *trackInfo) {
        if (handleTrackFrame->pre) {
            int preHoldFrame = handleTrackFrame->pre->getHoldFrame();
            if (preHoldFrame > 1)
                handleTrackFrame->pre->setHoldFrame(handleTrackFrame->pre->getHoldFrame() - 1);
            else
                removeTrackFrameInfo(handleTrackFrame->pre, trackInfo);
        }
        handleTrackFrame->setStartFrame(handleTrackFrame->getStartFrame() - 1);
        handleTrackFrame->setHoldFrame(handleTrackFrame->getHoldFrame() + 1);

        dumpTrackFrameIdx(trackInfo);
    }

    void L2R(TrackFrameInfo *handleTrackFrame, TrackInfo *trackInfo) {
        //fixme has bug
        cout << typeid(this).name() << " L2R: " << handleTrackFrame->getIdx() << endl;
        if (!_trackFrameInfotoRemoves->empty()) {
            TrackFrameInfo *delTfi = _trackFrameInfotoRemoves->back();
            _trackFrameInfotoRemoves->pop_back();

            //insert
            delTfi->setPre(handleTrackFrame->pre);
            handleTrackFrame->setPre(delTfi);
            _trackInfoHead->trackFrameInfos->insert(_trackInfoHead->trackFrameInfos->begin() + delTfi->getIdx(),
                                                    delTfi);
            handleTrackFrame->foreach([](TrackFrameInfo *tfiBackward) {
                tfiBackward->setIdx(tfiBackward->getIdx() + 1);
            }, handleTrackFrame);
            ///////////////////
            cout << typeid(this).name() << " recover: " << delTfi->getIdx() << endl;
        }
        else {
            if (handleTrackFrame->pre) {
                handleTrackFrame->pre->setHoldFrame(handleTrackFrame->pre->getHoldFrame() + 1);
            }
        }

        if (handleTrackFrame->getHoldFrame() > 1) {
            handleTrackFrame->setStartFrame(handleTrackFrame->getStartFrame() + 1);
            handleTrackFrame->setHoldFrame(handleTrackFrame->getHoldFrame() - 1);
        }
        else {
            removeTrackFrameInfo(handleTrackFrame, trackInfo);
        }
        updateContentEndFrame();
        dumpTrackFrameIdx(trackInfo);
    }

    void clearRemoveFrame() {
        _trackFrameInfotoRemoves->clear();
    }

    void dumpTrackFrameIdx(TrackInfo *trackInfo) {
        cout << typeid(this).name() << " track idx " << trackInfo->idx << ": ";
        trackInfo->getHeadTrackFrameInfo()->foreach([](TrackFrameInfo *tfi) {
            cout << " " << tfi->getIdx();
        });
        cout << endl;
    }

    int getCurrentFrame() {
        return _currentFrame;
    }

    void setCurrentFrame(int v) {
        _currentFrame = v;
    }

    void increaseCurrentFrame() {
        _currentFrame = (_currentFrame % _contentEndFrame) + 1;
    }

    void decreaseCurrentFrame() {
        if (_currentFrame == 1)
            _currentFrame = _contentEndFrame;
        else
            --_currentFrame;
    }

    vector<BaseTrackInfo *> *getTrackInfos() {
        return _trackInfos;
    }

    //
    void updateContentEndFrame() {
        if (_trackInfoHead) {
            int endFrame = 0;

            _trackInfoHead->foreach([&](BaseTrackInfo *trkInfo) {
                endFrame = trkInfo->getEndFrame();
                if (endFrame > _contentEndFrame)
                    _contentEndFrame = endFrame;
            });

            cout << typeid(this).name() << " update content end frame:" << _contentEndFrame << endl;
        }
    }

private:
    //
    int _currentFrame = 1;
    int _contentEndFrame = 0;

    void removeTrackFrameInfo(TrackFrameInfo *tfi, TrackInfo *trackInfo) {
        vector<TrackFrameInfo *>::iterator i = trackInfo->trackFrameInfos->begin();
        while (i != trackInfo->trackFrameInfos->end()) {
            if (*i == tfi) {
                trackInfo->trackFrameInfos->erase(i);
                break;
            } else {
                i++;
            }
        }
        TrackFrameInfo *nextTfi = tfi->next;
        if (nextTfi)
            nextTfi->foreach([](TrackFrameInfo *tfiBackward) {
                tfiBackward->setIdx(tfiBackward->getIdx() - 1);
            }, nextTfi);
        _trackFrameInfotoRemoves->push_back(tfi);
        tfi->remove();
    }


    TrackInfo *_trackInfoHead = nullptr;
    vector<TrackFrameInfo *> *_trackFrameInfotoRemoves;
    vector<BaseTrackInfo *> *_trackInfos;
};