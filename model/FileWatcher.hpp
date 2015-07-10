//
// Created by toramisu on 2015/7/8.
//

#ifndef SEQTRUAN_WATCHDOG_HPP
#define SEQTRUAN_WATCHDOG_HPP

#endif //SEQTRUAN_WATCHDOG_HPP

#include "QThread"
#include "QtCore"
#include "windows.h"

class FileWatcher : public QObject {
Q_OBJECT
public:
    FileWatcher() {
        moveToThread(&t);
        t.start();
    }

    ~FileWatcher() {
        t.quit();
        t.wait();
    }

    void start(QString imagePath){
        QMetaObject::invokeMethod(this, "work", Q_ARG(QString, imagePath));

    }
public slots:
    void work(QString absPath) {
        HANDLE hDir = CreateFile(
                absPath.toStdString().c_str(),
                FILE_LIST_DIRECTORY,
                FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
                NULL,
                OPEN_EXISTING,
                FILE_FLAG_BACKUP_SEMANTICS,
                NULL
        );

        int nCounter = 0;
        FILE_NOTIFY_INFORMATION strFileNotifyInfo[1024];
        DWORD dwBytesReturned = 0;

        while (TRUE) {
            if (ReadDirectoryChangesW(hDir, (LPVOID) &strFileNotifyInfo, sizeof(strFileNotifyInfo), FALSE,
                                      FILE_NOTIFY_CHANGE_LAST_WRITE, &dwBytesReturned, NULL, NULL) == 0) {
//                ErrorCheck(_T("Reading Directory Change"));
            }
            else {
//                QString::fromStdWString()
                QString filename = QString::fromStdWString(strFileNotifyInfo[0].FileName);
                qDebug() << "File Modified: " << filename;
                emit modified(filename);
                qDebug() << "Loop: " << nCounter++;
            }
        }
    }
signals:
    void modified(QString imagePath);

private:
    QThread t;
};