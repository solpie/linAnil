//
// Created by toramisu on 2015/7/7.
//
#pragma once
#ifndef SEQTRUAN_APPEXTERNAL_HPP
#define SEQTRUAN_APPEXTERNAL_HPP

#endif //SEQTRUAN_APPEXTERNAL_HPP

#include "stdlib.h"
#include "windows.h"
#include "FileWatcher.hpp"


string &replace_all(string &str, const string &old_value, const string &new_value) {
    while (true) {
        string::size_type pos(0);
        if ((pos = str.find(old_value)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else break;
    }
    return str;
}


string &replace_all_distinct(string &str, const string &old_value, const string &new_value) {
    for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
        if ((pos = str.find(old_value, pos)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else break;
    }
    return str;
}

class AppExternal {
public:

    static void editExternal(string path) {
        string csp = "\"C:\\Program Files\\CELSYS\\CLIP STUDIO\\CLIP STUDIO PAINT\\CLIPStudioPaint.exe\"";
        replace_all_distinct(path, "/", "\\");
        string cmd = csp + " " + path;
        WinExec(cmd.c_str(), WM_SHOWWINDOW);
    }

    static void setCursorVisible(bool b) {
        //todo 记录光标隐藏位置 显示光标时候恢复位置
        ShowCursor(b);
    }

//    static void startWatch(QString path) {
//        //todo move to thread
//        FileWatcher *wd = new FileWatcher();
//        wd->start(path);
////        HANDLE hDir = CreateFile(
////                path.toStdString().c_str(),
////                FILE_LIST_DIRECTORY,
////                FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
////                NULL,
////                OPEN_EXISTING,
////                FILE_FLAG_BACKUP_SEMANTICS,
////                NULL
////        );
////
////        int nCounter = 0;
////        FILE_NOTIFY_INFORMATION strFileNotifyInfo[1024];
////        DWORD dwBytesReturned = 0;
////
////        while (TRUE) {
////            if (ReadDirectoryChangesW(hDir, (LPVOID) &strFileNotifyInfo, sizeof(strFileNotifyInfo), FALSE,
////                                      FILE_NOTIFY_CHANGE_LAST_WRITE, &dwBytesReturned, NULL, NULL) == 0) {
//////                ErrorCheck(_T("Reading Directory Change"));
////            }
////            else {
//////                QString::fromStdWString()
////                QString filename = QString::fromStdWString(strFileNotifyInfo[0].FileName);
////                qDebug() << "File Modified: " << filename;
////                qDebug() << "Loop: " << nCounter++;
////            }
////        }
//    }
};