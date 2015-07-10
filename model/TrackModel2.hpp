//
// Created by toramisu on 2015/7/10.
//
#pragma once

#ifndef LINANIL_TRACKMODEL2_HPP
#define LINANIL_TRACKMODEL2_HPP

#endif //LINANIL_TRACKMODEL2_HPP

#include "TrackInfo.hpp"
#include "vector"
#include "boost/filesystem.hpp"

#include "iostream"
#include "windows.h"

using namespace boost;

#include <stack>

class TrackModel {
public:
    TrackModel() {
        _trackInfos = new vector<TrackInfo *>();
    }

    void walk() {
        boost::filesystem::path path = boost::filesystem::current_path();
        boost::filesystem::recursive_directory_iterator itr(path);
        while (itr != boost::filesystem::recursive_directory_iterator()) {
            cout << itr->path().string() << endl;
            ++itr;
        }
    }


    void newTrack(string name, string dirname = "") {
//    Evt_add("type", func1);
        TrackInfo *trackInfo = new TrackInfo(name);
        trackInfo->idx = _trackInfos->size();
        _trackInfos->push_back(trackInfo);
        TrackFrameInfo *pre = nullptr;
        if (dirname != "") {
//            QDir dir(dirname);
//            dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks);
//            const QFileInfoList fileinfolist = dir.entryInfoList();
//                    foreach(const QFileInfo &fi, fileinfolist) {
//                    if (fi.baseName() == "." || fi.baseName() == ".." || fi.baseName() == "") {
//                        continue;
//                    }
//                    if (fi.isDir() && fi.isReadable()) {
//                        // This is the conditional for recursion
////                walk( fi.absoluteFilePath() );
//                    }
//                    else {
//                        // This is where you might call your encrypting function
////                        qDebug() << "Image file: " << fi.absoluteFilePath();
////                        QImage *img = new QImage(fi.absoluteFilePath());
//                        TrackFrameInfo *trackFrameInfo = new TrackFrameInfo();
//
//                        trackFrameInfo->load(fi.absoluteFilePath());
//                        pre = trackFrameInfo->setPre(pre);
//                        trackFrameInfo->setTrackInfoIdx(trackInfo->idx);
////                        trackFrameInfo->payLoad = img;
//                        trackFrameInfo->setIdx(trackInfo->trackFrameInfos->size());
//                        trackFrameInfo->setStartFrame(trackFrameInfo->getIdx() + 1);
//                        trackFrameInfo->setHoldFrame(1);
//                        trackInfo->append(trackFrameInfo);
//                        if (!trackInfo->getHeadTrackFrameInfo()) {
//                            trackInfo->setHead(trackFrameInfo);
//                        }
//                    }
//                }
        }
        cout << this << "trackInfo frame count:" << trackInfo->getFrameCount();
//        if (sizeof(trackInfo->trackFrameInfos) > sequencePlayback->endFrameIdx) {
//            sequencePlayback->endFrameIdx = sizeof(trackInfo->trackFrameInfos);
//        }
//        Evt_dis(TrackModelEvent::NEW_TRACK, trackInfo);
    };
private:
    vector<TrackInfo *> *_trackInfos;

};