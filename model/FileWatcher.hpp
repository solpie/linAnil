//
// Created by toramisu on 2015/7/8.
//

#ifndef SEQTRUAN_WATCHDOG_HPP
#define SEQTRUAN_WATCHDOG_HPP

#endif //SEQTRUAN_WATCHDOG_HPP

//#include "QThread"
//#include "QtCore"
#include <thread>
#include "windows.h"
using namespace std;
void work(string absPath) {
    HANDLE hDir = CreateFile(
            absPath.c_str(),
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
//                string filename = QString::fromStdWString(strFileNotifyInfo[0].FileName);
            cout << "File Modified: " << strFileNotifyInfo[0].FileName<<endl;
//                emit modified(filename);
//                cout << "Loop: " << nCounter++;
        }
    }
}
class FileWatcher{
//Q_OBJECT
public:
    FileWatcher() {
//        moveToThread(&t);
//        t.start();
    }

    ~FileWatcher() {
//        t.quit();
//        t.wait();
    }

    void start(string imagePath){
//        QMetaObject::invokeMethod(this, "work", Q_ARG(QString, imagePath));
        std::thread t(work, imagePath);
        t.detach();
//        t.join();
    }

//signals:
//    void modified(QString imagePath);

//private:
//    QThread t;
};