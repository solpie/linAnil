//
// Created by toramisu on 2015/7/27.
//
#pragma once

#include	<stdio.h>
#include	<string.h>
#include <tclTomMath.h>
#include "sndfile.h"
/*	This will be the length of the buffer used to hold.frames while
**	we process them.
*/
#define        BUFFER_LEN    1024

/* libsndfile can handle more than 6 channels but we'll restrict it to 6. */
#define        MAX_CHANNELS    6

static vector<float> *getSamples(SNDFILE *infile, SF_INFO *info, double width, int channel, int step = 1) {
    int x = 0;
    int channels;
    long frames_per_buf, buffer_len;

    const float frames_per_bin = info->frames / (float) width;
    const long max_frames_per_bin = ceilf(frames_per_bin);
    float *data;
    long f_offset = 0;

    if (channel < 0 || channel >= info->channels) {
        printf("invalid channel\n");
        return nullptr;
    };

    data = malloc(sizeof(float) * max_frames_per_bin * info->channels);
    if (!data) {
        printf("out of memory.\n");
        return nullptr;
    };

    sf_seek(infile, 0, SEEK_SET);

    channels = (channel > 0) ? 1 : info->channels;

    frames_per_buf = floorf(frames_per_bin);
    buffer_len = frames_per_buf * info->channels;

    vector<float> *samples = new vector<float>;
    float *samples1 = new float[frames_per_buf];
    while ((sf_read_float(infile, data, buffer_len)) > 0) {
        int frame;
        for (frame = 0; frame < frames_per_buf; frame += step) {
            int ch;
            for (ch = 0; ch < info->channels; ch++) {
                if (channel > 0 && ch + 1 != channel)
                    continue;
                if (frame * info->channels + ch > buffer_len) {
                    fprintf(stderr, "index error!\n");
                    break;
                };
                {
                    const float sample_val = data[frame * info->channels + ch];
                    samples->push_back(sample_val);
                };
            };
        };

        x++;
        if (x > width) break;

        f_offset += frames_per_buf;
        frames_per_buf = floorf((x + 1) * frames_per_bin) - f_offset;
        buffer_len = frames_per_buf * info->channels;
    };

    free(data);
    return samples;
}


class WaveForm {
public:
    WaveForm() {

    }

    void test() {

        /* A SNDFILE is very much like a FILE in the Standard C library. The
        ** sf_open function return an SNDFILE* pointer when they sucessfully
        ** open the specified file.
        */
        SNDFILE *infile, *outfile;

        /* A pointer to an SF_INFO struct is passed to sf_open.
        ** On read, the library fills this struct with information about the file.
        ** On write, the struct must be filled in before calling sf_open.
        */
        SF_INFO sfinfo;
        int readcount;
        const char *infilename = "test.wav";

        /* The SF_INFO struct must be initialized before using it.
        */
        memset(&sfinfo, 0, sizeof(sfinfo));

        /* Here's where we open the input file. We pass sf_open the file name and
        ** a pointer to an SF_INFO struct.
        ** On successful open, sf_open returns a SNDFILE* pointer which is used
        ** for all subsequent operations on that file.
        ** If an error occurs during sf_open, the function returns a NULL pointer.
        **
        ** If you are trying to open a raw headerless file you will need to set the
        ** format and channels fields of sfinfo before calling sf_open(). For
        ** instance to open a raw 16 bit stereo PCM file you would need the following
        ** two lines:
        **
        **		sfinfo.format   = SF_FORMAT_RAW | SF_FORMAT_PCM_16 ;
        **		sfinfo.channels = 2 ;
        */
        if (!(infile = sf_open(infilename, SFM_READ, &sfinfo))) {    /* Open failed so print an error message. */
            printf("Not able to open input file %s.\n", infilename);
            /* Print the error message from libsndfile. */
            puts(sf_strerror(NULL));
            return;
        };

        if (sfinfo.channels > MAX_CHANNELS) {
            printf("Not able to process more than %d channels\n", MAX_CHANNELS);
            return;
        };

//        AGC agc;
//        calc_peak(infile, &sfinfo, 1024, 0, &agc);
        vector<float> *s = getSamples(infile, &sfinfo, 2048, 0,1);
//        vector<float>  *s = getSamples(infile, &sfinfo, 1024, 0);
        cout << "get Samples: " << s->size() << endl;


        /* While there are.frames in the input file, read them, process
        ** them and write them to the output file.
        */
//        while ((readcount = sf_read_double(infile, data, BUFFER_LEN))) {
//
//            process_data(data, readcount, sfinfo.channels);
//
//            sf_write_double(outfile, data, readcount);
//        };

        /* Close input and output files. */
        sf_close(infile);
//        sf_close(outfile);
    };

};