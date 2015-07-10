//
// Created by toramisu on 2015/6/24.
//
#pragma once
#ifndef SEQTRUAN_IMAGELOADER_HPP
#define SEQTRUAN_IMAGELOADER_HPP

#endif //SEQTRUAN_IMAGELOADER_HPP

//#include "QThread"
//#include "QImage"
//#include "QtCore"

using namespace std;

class ImageLoader {
public:

    ImageLoader() {
//        moveToThread(&t);
//        t.start();
    }

    ~ImageLoader() {
//        qDebug("Bye bye!");
//        t.quit();
//        t.wait();
    }

//    QImage *payLoad = nullptr;
//    QString imagePath;

    void load(std::string absPath) {
//        imagePath = absPath;
    }

//    _OBS

    void start() {
//        qDebug() << this << "Image loading in Thread:" << imagePath;
//        QMetaObject::invokeMethod(this, "completed", Q_ARG(QString, imagePath));
    }

//public slots:

    void completed(std::string absPath) {
//        payLoad = new QImage(absPath);
//        Evt_dis("LOAD_COMPLETE", nullptr)

//        qDebug() << this << "Image loaded!" << absPath;
//        dis("LOAD_COMPLETE", nullptr);
//        emit imageLoaded(payLoad);
    }

//signals:
//
//    void imageLoaded(QImage *image);


//private:
//    QThread t;
};