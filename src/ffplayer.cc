//
//  ffplayer.cpp
//  ffmpeg_tests
//
//  Created by chunlei on 2017/8/9.
//  Copyright © 2017年 itchunlei. All rights reserved.
//


#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#ifdef __cplusplus
}
#endif



#include "ffplayer.h"
void FFPlayer::Open(const std::string& file_name) {
    file_name_ = file_name;
    DoDemux();
}

void FFPlayer::Play() {

}

void FFPlayer::Pause() {

}

void FFPlayer::Stop() {

}


// private:
void FFPlayer::DoDemux() {
    av_register_all();
    AVFormatContext *avformat_ctx = avformat_alloc_context();
    if (avformat_open_input(&avformat_ctx, file_name_.c_str(), nullptr, nullptr) < 0) {
        //TODO: error
    }
    if (avformat_find_stream_info(avformat_ctx, nullptr) < 0) {
        //TODO: error
    }
    
    int audio_index = -1;
    int video_index = -1;
    
    for (int i = 0; i < avformat_ctx->nb_streams; i++) {
        auto type = avformat_ctx->streams[i]->codecpar->codec_type;
        switch (type) {
            case AVMEDIA_TYPE_VIDEO:
                std::cout << "AVMEDIA_TYPE_VIDEO: i: " << i  << std::endl;
                video_index = i;
                break;
            case AVMEDIA_TYPE_AUDIO:
                std::cout << "AVMEDIA_TYPE_AUDIO: i: " << i  << std::endl;
                audio_index = i;
                break;
            case AVMEDIA_TYPE_SUBTITLE:
                std::cout << "AVMEDIA_TYPE_SUBTITLE: i: " << i  << std::endl;
                break;
            case AVMEDIA_TYPE_ATTACHMENT:
                std::cout << "AVMEDIA_TYPE_ATTACHMENT: i: " << i  << std::endl;
                break;
            default:
                break;
        }
    }
    
    
    // decode video
    AVCodec* video_codec = avcodec_find_decoder(avformat_ctx->streams[video_index]->codecpar->codec_id);
    AVCodecContext *avcodec_ctx = avcodec_alloc_context3(video_codec);
    if (avcodec_open2(avcodec_ctx, video_codec, nullptr) < 0) {
        //TODO: error
    }
    
    printf("bit_rate = %lld \n", avcodec_ctx->bit_rate);
    printf("sample_rate = %d \n", avcodec_ctx->sample_rate);
    printf("channels = %d \n", avcodec_ctx->channels);
    printf("code_name = %s \n", avcodec_ctx->codec->name);
    printf("block_align = %d\n",avcodec_ctx->block_align);
    
    
    AVPacket *packet = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
    while (av_read_frame(avformat_ctx, packet) >= 0) {
        if (packet->stream_index == video_index) {
            avcodec_send_packet(avcodec_ctx, packet);
            avcodec_receive_frame(avcodec_ctx, frame);
//            if (frame)
//            std::cout << "width:" << frame->width << std::endl;
            // std::cout << packet.duration << std::endl;
        } else if (packet->stream_index == audio_index) {
            // std::cout << packet.duration << std::endl;
        }
    }
    
    
    
   // avformat_free_context(avformat_ctx);
}

