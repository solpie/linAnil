//
// Created by toramisu on 2015/7/7.
//
#pragma once
#ifndef SEQTRUAN_APPEXTERNAL_HPP
#define SEQTRUAN_APPEXTERNAL_HPP

#endif //SEQTRUAN_APPEXTERNAL_HPP

#include "stdlib.h"
#include "QString"
#include "windows.h"
#include "FileWatcher.hpp"
class AppExternal {

public:
    static void editExternal(QString path) {
        QString csp = "C:\\Program Files\\CELSYS\\CLIP STUDIO\\CLIP STUDIO PAINT\\CLIPStudioPaint.exe";
        QString cmd = csp + " " + path;
        system(cmd.toStdString().c_str());
    }
    static void setCursorVisible(bool b) {
        //todo 记录光标隐藏位置 显示光标时候恢复位置
        ShowCursor(b);
    }
    static void startWatch(QString path) {
        //todo move to thread
        FileWatcher *wd = new FileWatcher();
        wd->start(path);
//        HANDLE hDir = CreateFile(
//                path.toStdString().c_str(),
//                FILE_LIST_DIRECTORY,
//                FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
//                NULL,
//                OPEN_EXISTING,
//                FILE_FLAG_BACKUP_SEMANTICS,
//                NULL
//        );
//
//        int nCounter = 0;
//        FILE_NOTIFY_INFORMATION strFileNotifyInfo[1024];
//        DWORD dwBytesReturned = 0;
//
//        while (TRUE) {
//            if (ReadDirectoryChangesW(hDir, (LPVOID) &strFileNotifyInfo, sizeof(strFileNotifyInfo), FALSE,
//                                      FILE_NOTIFY_CHANGE_LAST_WRITE, &dwBytesReturned, NULL, NULL) == 0) {
////                ErrorCheck(_T("Reading Directory Change"));
//            }
//            else {
////                QString::fromStdWString()
//                QString filename = QString::fromStdWString(strFileNotifyInfo[0].FileName);
//                qDebug() << "File Modified: " << filename;
//                qDebug() << "Loop: " << nCounter++;
//            }
//        }
    }
};