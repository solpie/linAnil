//
// Created by toramisu on 2015/6/16.
//
#pragma once
#ifndef SEQTRUAN_TRACKMODEL_H
#define SEQTRUAN_TRACKMODEL_H

#endif //SEQTRUAN_TRACKMODEL_H

#include "utils/Singleton.hpp"
#include <functional>
#include <vector>
#include "events/Event.hpp"
//#include "model/playback/SequencePlayback.hpp"
//#include "model/playback/AudioPlayback.hpp"

#include "TrackInfo.hpp"
#include "TrackFrameInfo.hpp"


#include <iostream>

class TrackModel {
public:
    TrackModel() {
        sequencePlayback = new SequencePlayback();
        audioPlayback = new AudioPlayback();
        _trackInfos = new vector<TrackInfo *>();
    }


    void newTrack(QString name, QString dirname = "") {
//    Evt_add("type", func1);
        TrackInfo *trackInfo = new TrackInfo(name);
        trackInfo->idx = _trackInfos->size();
        _trackInfos->push_back(trackInfo);
        TrackFrameInfo *pre = nullptr;
        if (dirname != "") {
            QDir dir(dirname);
            dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks);
            const QFileInfoList fileinfolist = dir.entryInfoList();
                    foreach(const QFileInfo &fi, fileinfolist) {
                    if (fi.baseName() == "." || fi.baseName() == ".." || fi.baseName() == "") {
                        continue;
                    }
                    if (fi.isDir() && fi.isReadable()) {
                        // This is the conditional for recursion
//                walk( fi.absoluteFilePath() );
                    }
                    else {
                        // This is where you might call your encrypting function
//                        qDebug() << "Image file: " << fi.absoluteFilePath();
//                        QImage *img = new QImage(fi.absoluteFilePath());
                        TrackFrameInfo *trackFrameInfo = new TrackFrameInfo();

                        trackFrameInfo->load(fi.absoluteFilePath());
                        pre = trackFrameInfo->setPre(pre);
                        trackFrameInfo->setTrackInfoIdx(trackInfo->idx);
//                        trackFrameInfo->payLoad = img;
                        trackFrameInfo->setIdx(trackInfo->trackFrameInfos->size());
                        trackFrameInfo->setStartFrame(trackFrameInfo->getIdx() + 1);
                        trackFrameInfo->setHoldFrame(1);
                        trackInfo->append(trackFrameInfo);
                        if (!trackInfo->getHeadTrackFrameInfo()) {
                            trackInfo->setHead(trackFrameInfo);
                        }
                    }
                }
        }
        qDebug() << this << "trackInfo frame count:" << trackInfo->getFrameCount();
        if (sizeof(trackInfo->trackFrameInfos) > sequencePlayback->endFrameIdx) {
            sequencePlayback->endFrameIdx = sizeof(trackInfo->trackFrameInfos);
        }
        Evt_dis(TrackModelEvent::NEW_TRACK, trackInfo);
    };

    float getZoomRaito() {
        return zoomRaito;
    }

    //max 1 min 0.025 (1/40)
    void setZoomLevel(float raito) {
        zoomRaito = raito;
        frameWidth = MAX_FRAME_WIDTH * raito;
        Evt_dis(TrackModelEvent::SET_ZOOM_LEVEL, nullptr);
    }

    vector<TrackFrameInfo *> *getRenderFrame2(int frameIdx) {
        vector<TrackFrameInfo *> *images = new vector<TrackFrameInfo *>;
        for (TrackInfo *trackInfo:*_trackInfos) {
            if (!trackInfo->visible)
                continue;
            TrackFrameInfo *trackFrameInfo = trackInfo->getHeadTrackFrameInfo();
            int trackFrameIdx = frameIdx - trackInfo->getStartFrame() + 1;
            while (trackFrameInfo) {
//                qDebug() << this << "idx:" << trackFrameInfo->getIdx()
//                << "start:" << trackFrameInfo->getStartFrame()
//                << "end:" << trackFrameInfo->getEndFrame();
                //todo ²éÕÒÓÅ»¯ trackEndFrame ÅÐ¶Ï
                if (trackFrameIdx >= trackFrameInfo->getStartFrame()) {
                    if (trackFrameIdx <= trackFrameInfo->getEndFrame()) {
                        trackFrameInfo->opacity = trackInfo->getOpacity();
                        images->push_back(trackFrameInfo);
//                    trackFrameInfo->next
                        break;
                    }

                }
                trackFrameInfo = trackFrameInfo->next;
            }
        }
        return images;
    }

    TrackInfo *getTrackInfo(int tIdx) { return _trackInfos->at(tIdx); }

    TrackFrameInfo *getTrackFrameInfo(int tIdx, int tfIdx) { return getTrackInfo(tIdx)->trackFrameInfos->at(tfIdx); }

    int frameWidth = 40;
    int trackWidth = 1280;
//    SequencePlayback *sequencePlayback;
//    AudioPlayback *audioPlayback;
protected:
    float zoomRaito = 1.0;
private:
    int MAX_FRAME_WIDTH = 40;
    vector<TrackInfo *> *_trackInfos;

};