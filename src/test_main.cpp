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
#define AV_FILE_PATH "/Users/chunlei/Desktop/ffplayer/av_test_files/radar.mp3"

int main(int argc, char* argv[]) {
    
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        printf("Could not initialize SDL -%s\n", SDL_GetError());
        return -1;
    }
    
    
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
        if (av_format_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audio_index = i;
            printf("find a audio stream.\n");
        }
    }
    
    AVCodecParameters *codec_params = av_format_ctx->streams[audio_index]->codecpar;
    AVCodec* codec = avcodec_find_decoder(codec_params->codec_id);
    if (codec == NULL) {
        printf("Codec not found.\n");
        return -1;
    }
    
    AVCodecContext* codec_ctx = avcodec_alloc_context3(codec);
    
    if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
        printf("Could not open codec.\n");
        return -1;
    }
    
    printf("bit_rate = %lld \n", codec_ctx->bit_rate);
    printf("sample_rate = %d \n", codec_ctx->sample_rate);
    printf("channels = %d \n", codec_ctx->channels);
    printf("code_name = %s \n", codec_ctx->codec->name);
    printf("block_align = %d\n",codec_ctx->block_align);
    
    
    AVPacket *packet = (AVPacket*)malloc(sizeof(AVPacket));
    av_init_packet(packet);
    
    uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
    int out_nb_samples = 1024;
    enum AVSampleFormat sample_fmt = AV_SAMPLE_FMT_S16;
    
    int out_sample_rate = 44100;
    int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
    int buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, sample_fmt, 1);
    
    uint8_t *buffer = (uint8_t*)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
    
    
    //Frame
    AVFrame *frame = av_frame_alloc();
    uint32_t ret,len = 0;
    int got_picture;
    
    int64_t in_channel_layout = av_get_default_channel_layout(codec_ctx->channels);
    
    struct SwrContext* convert_ctx = swr_alloc();
    convert_ctx = swr_alloc_set_opts(convert_ctx, out_channel_layout, sample_fmt, out_sample_rate,
                                     in_channel_layout, codec_ctx->sample_fmt, codec_ctx->sample_rate, 0, NULL);
    
    
    swr_init(convert_ctx);
    
    int index = 0;
    
    while (av_read_frame(av_format_ctx, packet) >= 0) {
        printf("index: %d\n", index);
        if (packet->stream_index == audio_index) {
            
            printf("====\n");
        }
        
        index++ ;
        av_free_packet(packet);
    }
    
    swr_free(&convert_ctx);
    
    return 0;
}
