//
//  test_main.cpp
//  ffmpeg_tests
//
//  Created by chunlei on 2017/8/3.
//  Copyright © 2017年 itchunlei. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "SDL.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
#include "libavdevice/avdevice.h"
#ifdef __cplusplus
}
#endif
#define MAX_AUDIO_FRAME_SIZE  192000
#define AV_FILE_PATH "/Users/chunlei/Desktop/ffplayer/av_test_files/video.mp4"


#include "ffplayer.h"

int main(int argc, char* argv[]) {
    
    
    FFPlayer player;
    player.Open(AV_FILE_PATH);
    
//    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
//        printf("Could not initialize SDL -%s\n", SDL_GetError());
//        return -1;
//    }
//    
//    
//    SDL_Window* window = SDL_CreateWindow("ffplayer", 0, 0, 640, 320, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
//    if (!window) {
//        return -1;
//    }
//    
//    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
//    
//    
//    SDL_Event event;
//    for(;;) {
//        SDL_WaitEvent(&event);
//        if (event.type == SDL_QUIT) {
//            break;
//        }
//        printf("event.type: %d\n", event.type);
//    }
    return 0;
}
