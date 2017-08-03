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
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#ifdef __cplusplus
}
#endif

#define AV_FILE_PATH "/Users/chunlei/Desktop/ffplayer/av_test_files/radar.mp3"

int main(int argc, char* argv[]) {
    av_register_all();
    avformat_network_init();
    AVFormatContext *av_format_ctx;
    av_format_ctx = avformat_alloc_context();
    if (avformat_open_input(&av_format_ctx, AV_FILE_PATH, NULL, NULL) < 0){
        printf("avformat_open_input() error.\n");
    }
    
    if (avformat_find_stream_info(av_format_ctx, NULL) < 0) {
        
    }
    
    int audio_index = -1;
    for (int i = 0; i < av_format_ctx->nb_streams; i++) {
        if (av_format_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
            audio_index = i;
            printf("find a audio stream.\n");
        }
    }
    
    AVCodecContext *codec_ctx;
    codec_ctx = av_format_ctx->streams[audio_index]->codec;
    AVCodec* codec = avcodec_find_decoder(codec_ctx->codec_id);
    if (codec == NULL) {
        printf("Codec not found.\n");
        return -1;
    }
    
    if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
        printf("Could not open codec.\n");
        return -1;
    }
    
    
    static AVPacket packet;
    
    printf("bit_rate = %lld \n", codec_ctx->bit_rate);
    printf("sample_rate = %d \n", codec_ctx->sample_rate);
    printf("channels = %d \n", codec_ctx->channels);
    printf("code_name = %s \n", codec_ctx->codec->name);
    printf("block_align = %d\n",codec_ctx->block_align);
    
    return 0;
}
