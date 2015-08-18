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

#include "boost/filesystem.hpp"

class ImageInfo {
public:
    int id = -1;
    string path;
    string filename;
    int width;
    int height;
    int thumbId = -1;
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

        return imgInfo;
    }

    void update(ImageInfo *imgInfo, string absPath) {
        imgInfo->path = absPath;
        imgInfo->id = nvgCreateImage(_vg, absPath.c_str(), 0);
    }


    void createPng(string path, string name, int n, int w, int h) {
        //mk dir
        string cmd = "mkdir " + path;
        system(cmd.c_str());

        boost::filesystem::path path1(path);
        path1 /= name;
        name = path1.string();
        ///
        int comp = 4;//rgba
        int ndata = w * h * comp;

        char str[10];

        unsigned char *zero_pixels = (unsigned char *) malloc(ndata);
        memset(zero_pixels, 0, ndata);
        string nname;
        for (int i = 0; i < n; ++i) {
            sprintf(str, "%03d", i + 1);
            nname = name + "#" + str + ".png";
            stbi_write_png(nname.c_str(), w, h, comp, zero_pixels, 0);
        }
        free(zero_pixels);
    }

private:

    void createThumb(string path, ImageInfo *imgInfo) {
        cout << typeid(this).name() << " createThumb " << path << endl;
        int comp, w, h;
        unsigned char *input_pixels;
        unsigned char *output_pixels;
        input_pixels = stbi_load(path.c_str(), &w, &h, &comp, 0);
//        imgInfo->id = nvgCreateImageRGBA(_vg, imgInfo->width, imgInfo->height, 0, input_pixels);

        int out_w = 300;
        int out_h = h * out_w / double(w);


        imgInfo->thumbW = out_w;
        imgInfo->thumbH = out_h;
        imgInfo->thumbRatio = double(out_h) / out_w;
        output_pixels = (unsigned char *) malloc(out_w * out_h * comp);
        stbir_resize_uint8(input_pixels, w, h, 0, output_pixels, out_w, out_h, 0, comp);

//        imgInfo->thumbId = nvgCreateImageRGBA(_vg, out_w, out_h, 0, output_pixels);
//        imgInfo->thumbId = nvgCreateImageMem(_vg, 0, output_pixels, out_w * out_h * comp);
        stbi_write_png("resize.png", out_w, out_h, comp, output_pixels, 0);
        imgInfo->thumbId = nvgCreateImage(_vg, "resize.png", 0);
        free(output_pixels);
    }


    map<string, ImageInfo *> _images;
    NVGcontext *_vg;
};