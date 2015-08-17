//
// Created by toramisu on 2015/6/24.
//
#pragma once

using namespace std;

#include "utils/Singleton.hpp"
#include "nanovg/nanovg.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "utils/stb/stb_image_write.h"
#include "utils/stb/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "utils/stb/stb_image_resize.h"

class ImageInfo {
public:
    int id = -1;
    int thumbId = -1;
    string path;
    string filename;
    int width;
    int height;
    int thumbW;
    int thumbH;
    double thumbRatio;
};

class ImageLoader : public Singleton<ImageLoader> {
public:
    void setContext(NVGcontext *vg) { _vg = vg; }

    ImageInfo *load(std::string absPath) {
        if (_images.find(absPath) != _images.end())
            return _images[absPath];

        ImageInfo *imgInfo = new ImageInfo();
        imgInfo->path = absPath;
        imgInfo->id = nvgCreateImage(_vg, absPath.c_str(), 0);
        nvgImageSize(_vg, imgInfo->id, &imgInfo->width, &imgInfo->height);
        _images[absPath] = imgInfo;
        //todo create thumb image
        createThumb(absPath, imgInfo);
        return imgInfo;
    }

    //
private:

    void createThumb(string path, ImageInfo *imgInfo) {
        cout << typeid(this).name() << " createThumb " << path << endl;
        int comp, w, h;
        unsigned char *input_pixels;
        unsigned char *output_pixels;
        input_pixels = stbi_load(path.c_str(), &w, &h, &comp, 0);
//        imgInfo->id = nvgCreateImageRGBA(_vg, imgInfo->width, imgInfo->height, 0, input_pixels);

        int out_w = w * .5;
        int out_h = h * 0.5;
        imgInfo->thumbW = out_w;
        imgInfo->thumbH = out_h;
        imgInfo->thumbRatio = double(out_h) / out_w;
        output_pixels = (unsigned char *) malloc(out_w * out_h * comp);
        stbir_resize_uint8(input_pixels, w, h, 0, output_pixels, out_w, out_h, 0, comp);
        //
        imgInfo->thumbId = nvgCreateImageRGBA(_vg, out_w, out_h, 0, output_pixels);
//        imgInfo->thumbId = nvgCreateImageMem(_vg, 0, output_pixels, out_w * out_h * comp);
//        stbi_write_png("resize.png", out_w, out_h, comp, output_pixels,0);
//        imgInfo->thumbId = nvgCreateImage(_vg, "resize.png", 0);
        free(output_pixels);

    }


    map<string, ImageInfo *> _images;
    NVGcontext *_vg;
};