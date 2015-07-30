//
// Created by toramisu on 2015/6/24.
//
#pragma once

using namespace std;

#include "utils/Singleton.hpp"
#include "nanovg/nanovg.h"
#include "libpng16/png.h"
class ImageInfo {
public:
    int id = -1;
    string path;
    int width;
    int height;
};

class ImageLoader : public Singleton<ImageLoader> {
public:
    void setContext(NVGcontext *vg) { _vg = vg; }

    ImageInfo *load(std::string absPath) {
        if (_images.find(absPath) != _images.end())
            return _images[absPath];

        ImageInfo *imgInfo = new ImageInfo();
        imgInfo->id = nvgCreateImage(_vg, absPath.c_str(), 0);
        imgInfo->path = absPath;
        nvgImageSize(_vg, imgInfo->id, &imgInfo->width, &imgInfo->height);
        _images[absPath] = imgInfo;
        //todo create thumb image
        return imgInfo;
    }
    //
private:
    map<string, ImageInfo *> _images;
    NVGcontext *_vg;
};