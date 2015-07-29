#include <SDL2/SDL.h>
#undef main


// prototype for our audio callback
// see the implementation for more information
void my_audio_callback(void *userdata, Uint8 *stream, int len);

// variable declarations
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play


/*
** PLAYING A SOUND IS MUCH MORE COMPLICATED THAN IT SHOULD BE
*/
int test4() {

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        return 1;

    // local variables
    static Uint32 wav_length; // length of our sample
    static Uint8 *wav_buffer; // buffer containing our audio file
    static SDL_AudioSpec wav_spec; // the specs of our piece of music


    /* Load the WAV */
    // the specs, length and buffer of our wav are filled
    if (SDL_LoadWAV("test\\test.wav", &wav_spec, &wav_buffer, &wav_length) == NULL) {
        return 1;
    }
    // set the callback function
    wav_spec.callback = my_audio_callback;
    wav_spec.userdata = NULL;
    // set our global static variables
    audio_pos = wav_buffer; // copy sound buffer
    audio_len = wav_length; // copy file length

    /* Open the audio device */
    if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
        fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
        exit(-1);
    }

    /* Start playing */
    SDL_PauseAudio(0);
    // wait until we're don't playing
//    while (audio_len > 0) {
//        SDL_Delay(100);
//    }

    // shut everything down
//    SDL_CloseAudio();
//    SDL_FreeWAV(wav_buffer);

}

// audio callback function
// here you have to copy the data of your audio buffer into the
// requesting audio buffer (stream)
// you should only copy as much as the requested length (len)
void my_audio_callback(void *userdata, Uint8 *stream, int len) {

    if (audio_len == 0)
        return;

    len = (len > audio_len ? audio_len : len);
    //SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

    audio_pos += len;
    audio_len -= len;
}




#include "stdlib.h"
#include "SDL/SDL.h"
// *** IF USING XCODE ON MACOS X, CHANGE THE FOLLOWING LINE TO:  #include "SDL_mixer/SDL_mixer.h"
#include "SDL2/SDL_mixer.h"

int test5()
{
//    SDL_Surface *screen;			//Pointer to the main screen surface
    Mix_Chunk *sound = NULL;		//Pointer to our sound, in memory
    int channel;				//Channel on which our sound is played

    int audio_rate = 22050;			//Frequency of audio playback
    Uint16 audio_format = AUDIO_S16SYS; 	//Format of the audio we're playing
    int audio_channels = 2;			//2 channels = stereo
    int audio_buffers = 4096;		//Size of the audio buffers in memory

    //Initialize BOTH SDL video and SDL audio
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    //Initialize SDL_mixer with our chosen audio settings
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
        printf("Unable to initialize audio: %s\n", Mix_GetError());
        exit(1);
    }

    //Load our WAV file from disk
    sound = Mix_LoadWAV("test\\test.wav");
    if(sound == NULL) {
        printf("Unable to load WAV file: %s\n", Mix_GetError());
    }

    //Set the video mode to anything, just need a window
//    screen = SDL_SetVideoMode(320, 240, 0, SDL_ANYFORMAT);
//    if (screen == NULL) {
//        printf("Unable to set video mode: %s\n", SDL_GetError());
//        return 1;
//    }

    //Play our sound file, and capture the channel on which it is played
    channel = Mix_PlayChannel(-1, sound, 0);
    if(channel == -1) {
        printf("Unable to play WAV file: %s\n", Mix_GetError());
    }
    //Wait until the sound has stopped playing
//    while(Mix_Playing(channel) != 0);
    Mix_Playing(channel);

    int ret= Mix_SetMusicPosition(20);

    //Release the memory allocated to our sound
//    Mix_FreeChunk(sound);
//
//    //Need to make sure that SDL_mixer and SDL have a chance to clean up
//    Mix_CloseAudio();
//    SDL_Quit();

    //Return success!
    return 0;
}
