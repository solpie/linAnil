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


//#define NO_FREETYPE

//#include "utils/pngwriter/pngwriter.h"

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

#define PNGWRITER_DEFAULT_COMPRESSION (6)
#define PNG_gAMA_SUPPORTED
#define PNG_STDIO_SUPPORTED
#define PNG_SETJMP_SUPPORTED

#include <pngconf.h>
#include <png.h>

class pngCreator {
public:
    int width_;
    int height_;
    int backgroundcolour_;
    int compressionlevel_;

    unsigned char **graph_;
    double filegamma_;

    char *filename_;
    char *textauthor_;
    char *textdescription_;
    char *texttitle_;
    char *textsoftware_;
    int bit_depth_ = 16;

    pngCreator() {

    }

    pngCreator(int x, int y, int backgroundcolour, const char *filename) {
        width_ = x;
        height_ = y;
        backgroundcolour_ = backgroundcolour;
        compressionlevel_ = -2;
        filegamma_ = 0.6;

        textauthor_ = new char[255];
        textdescription_ = new char[255];
        texttitle_ = new char[strlen(filename) + 1];
        textsoftware_ = new char[255];
        filename_ = new char[strlen(filename) + 1];

        strcpy(textauthor_, "");
        strcpy(textdescription_, "");
        strcpy(textsoftware_, "");
        strcpy(texttitle_, filename);
        strcpy(filename_, filename);

        if ((width_ < 0) || (height_ < 0)) {
            std::cerr <<
            " PNGwriter::pngwriter - ERROR **: Constructor called with negative height or width. Setting width and height to 1." <<
            std::endl;
            height_ = 1;
            width_ = 1;
        }

        if (backgroundcolour_ > 65535) {
            std::cerr <<
            " PNGwriter::pngwriter - WARNING **: Constructor called with background colour greater than 65535. Setting to 65535." <<
            std::endl;
            backgroundcolour_ = 65535;
        }

        if (backgroundcolour_ < 0) {
            std::cerr <<
            " PNGwriter::pngwriter - WARNING **: Constructor called with background colour lower than 0. Setting to 0." <<
            std::endl;
            backgroundcolour_ = 0;
        }

        int kkkk;

//        bit_depth_ = 16; //Default bit depth for new images

        graph_ = (png_bytepp) malloc(height_ * sizeof(png_bytep));
        if (graph_ == NULL) {
            std::cerr << " PNGwriter::pngwriter - ERROR **:  Not able to allocate memory for image." << std::endl;
        }

        for (kkkk = 0; kkkk < height_; kkkk++) {
            graph_[kkkk] = (png_bytep) malloc(6 * width_ * sizeof(png_byte));
            if (graph_[kkkk] == NULL) {
                std::cerr << " PNGwriter::pngwriter - ERROR **:  Not able to allocate memory for image." << std::endl;
            }
        }

        if (graph_ == NULL) {
            std::cerr << " PNGwriter::pngwriter - ERROR **:  Not able to allocate memory for image." << std::endl;
        }

        if (backgroundcolour_ == 0)
            for (int vhhh = 0; vhhh < height_; vhhh++)
                memset(graph_[vhhh],
                       (char) backgroundcolour_,
                       width_ * 6);
        else {
            int tempindex;
            for (int hhh = 0; hhh < width_; hhh++) {
                for (int vhhh = 0; vhhh < height_; vhhh++) {
                    //graph_[vhhh][6*hhh + i] where i = 0 to 5
                    tempindex = 6 * hhh;
                    graph_[vhhh][tempindex] = (char) floor(((double) backgroundcolour_) / 256);
                    graph_[vhhh][tempindex + 1] = (char) (backgroundcolour_ % 256);
                    graph_[vhhh][tempindex + 2] = (char) floor(((double) backgroundcolour_) / 256);
                    graph_[vhhh][tempindex + 3] = (char) (backgroundcolour_ % 256);
                    graph_[vhhh][tempindex + 4] = (char) floor(((double) backgroundcolour_) / 256);
                    graph_[vhhh][tempindex + 5] = (char) (backgroundcolour_ % 256);
                }
            }
        }
    }

    void close() {
        FILE *fp;
        png_structp png_ptr;
        png_infop info_ptr;

        fp = fopen(filename_, "wb");
        if (fp == NULL) {
            std::cerr << " PNGwriter::close - ERROR **: Error creating file (fopen() returned NULL pointer)." <<
            std::endl;
            perror(" PNGwriter::close - ERROR **");
            return;
        }

        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        info_ptr = png_create_info_struct(png_ptr);
        png_init_io(png_ptr, fp);
        if (compressionlevel_ != -2) {
            png_set_compression_level(png_ptr, compressionlevel_);
        }
        else {
            png_set_compression_level(png_ptr, PNGWRITER_DEFAULT_COMPRESSION);
        }

        png_set_IHDR(png_ptr, info_ptr, width_, height_,
                     bit_depth_, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);


        time_t gmt;
        png_time mod_time;
        png_text text_ptr[5];
        int entries = 4;
        time(&gmt);
        png_convert_from_time_t(&mod_time, gmt);
        png_set_tIME(png_ptr, info_ptr, &mod_time);
        /* key is a 1-79 character description of type char* */
        char key_title[] = "";
        text_ptr[0].key = key_title;
        text_ptr[0].text = texttitle_;
        text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;
        char key_author[] = "";
        text_ptr[1].key = key_author;
        text_ptr[1].text = textauthor_;
        text_ptr[1].compression = PNG_TEXT_COMPRESSION_NONE;
        char key_descr[] = "";
        text_ptr[2].key = key_descr;
        text_ptr[2].text = textdescription_;
        text_ptr[2].compression = PNG_TEXT_COMPRESSION_NONE;
        char key_software[] = "";
        text_ptr[3].key = key_software;
        text_ptr[3].text = textsoftware_;
        text_ptr[3].compression = PNG_TEXT_COMPRESSION_NONE;
#if defined(PNG_TIME_RFC1123_SUPPORTED)
        char key_create[] = "Creation Time";
        text_ptr[4].key = key_create;
        char textcrtime[29] = "tIME chunk is not present...";
#if (PNG_LIBPNG_VER < 10600)
   textcrtime[28] = '\0';
   memcpy(textcrtime,
          png_convert_to_rfc1123(png_ptr, &mod_time),
          29);
   textcrtime[sizeof(text_ptr[4].text) - 1] = '\0';
#else
        png_convert_to_rfc1123_buffer(textcrtime, &mod_time);
#endif
        text_ptr[4].text = textcrtime;
        text_ptr[4].compression = PNG_TEXT_COMPRESSION_NONE;
        entries++;
#endif
        png_set_text(png_ptr, info_ptr, text_ptr, entries);

        png_write_info(png_ptr, info_ptr);
        png_write_image(png_ptr, graph_);
        png_write_end(png_ptr, info_ptr);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
    }
//    void abort_(const char * s, ...)
//    {
//        va_list args;
//        va_start(args, s);
//        vfprintf(stderr, s, args);
//        fprintf(stderr, "\n");
//        va_end(args);
//        abort();
//    }
//
//    png_structp png_ptr;
//    png_infop info_ptr;
//    void write_png_file(char* file_name)
//    {
//        /* create file */
//        FILE *fp = fopen(file_name, "wb");
//        if (!fp)
//            abort_("[write_png_file] File %s could not be opened for writing", file_name);
//
//
//        /* initialize stuff */
//        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//        if (!png_ptr)
//            abort_("[write_png_file] png_create_write_struct failed");
//
//        info_ptr = png_create_info_struct(png_ptr);
//        if (!info_ptr)
//            abort_("[write_png_file] png_create_info_struct failed");
//
//        if (setjmp(png_jmpbuf(png_ptr)))
//            abort_("[write_png_file] Error during init_io");
//
//        png_init_io(png_ptr, fp);
//
//
//        /* write header */
//        if (setjmp(png_jmpbuf(png_ptr)))
//            abort_("[write_png_file] Error during writing header");
//
//        png_set_IHDR(png_ptr, info_ptr, width_, height_,
//                     16, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
//                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
//
//        png_write_info(png_ptr, info_ptr);
//
//
//        /* write bytes */
//        if (setjmp(png_jmpbuf(png_ptr)))
//            abort_("[write_png_file] Error during writing bytes");
//
//        png_write_image(png_ptr, row_pointers);
//
//
//        /* end write */
//        if (setjmp(png_jmpbuf(png_ptr)))
//            abort_("[write_png_file] Error during end of write");
//
//        png_write_end(png_ptr, NULL);
//
//        /* cleanup heap allocation */
//        for (y=0; y<height; y++)
//            free(row_pointers[y]);
//        free(row_pointers);
//
//        fclose(fp);
//    }

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
        createThumb(absPath, imgInfo);
        return imgInfo;
    }

    void update(ImageInfo *imgInfo, string absPath) {
        imgInfo->path = absPath;
        imgInfo->id = nvgCreateImage(_vg, absPath.c_str(), 0);
    }

private:

    void createThumb(string path, ImageInfo *imgInfo) {
        cout << typeid(this).name() << " createThumb " << path << endl;
        int comp, w, h;
        unsigned char *input_pixels;
        unsigned char *output_pixels;
        input_pixels = stbi_load(path.c_str(), &w, &h, &comp, 0);
//        imgInfo->id = nvgCreateImageRGBA(_vg, imgInfo->width, imgInfo->height, 0, input_pixels);

        int out_w = 1;
        int out_h = h * out_w / double(w);


        imgInfo->thumbW = out_w;
        imgInfo->thumbH = out_h;
        imgInfo->thumbRatio = double(out_h) / out_w;
        output_pixels = (unsigned char *) malloc(out_w * out_h * comp);
        stbir_resize_uint8(input_pixels, w, h, 0, output_pixels, out_w, out_h, 0, comp);

        //
//        imgInfo->thumbId = nvgCreateImageRGBA(_vg, out_w, out_h, 0, output_pixels);
//        imgInfo->thumbId = nvgCreateImageMem(_vg, 0, output_pixels, out_w * out_h * comp);
        stbi_write_png("resize.png", out_w, out_h, comp, output_pixels, 0);
        imgInfo->thumbId = nvgCreateImage(_vg, "resize.png", 0);
        free(output_pixels);

//        pngCreator png(300,300,0,"test.png");
//        png.close();
//        pngCreator png;
//        png.write_png_file("test.png", 300, 300);
    }


    map<string, ImageInfo *> _images;
    NVGcontext *_vg;
};