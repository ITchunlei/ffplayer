//
//  ffplayer.hpp
//  ffmpeg_tests
//
//  Created by chunlei on 2017/8/9.
//  Copyright © 2017年 itchunlei. All rights reserved.
//

#ifndef FFPLAYER_H
#define FFPLAYER_H
#include <string>
class IPlayerInterface {
public:
    virtual void Open(const std::string& file_name) = 0;
    virtual void Play() = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;
};
class FFPlayer final : public IPlayerInterface {
public:
    FFPlayer() {};
    virtual ~FFPlayer() {};
    void Open(const std::string& file_name) override;
    void Pause() override;
    void Play() override;
    void Stop() override;
private:
    void DoDemux();
    
private:
    std::string file_name_;
};
#endif /* FFPLAYER_H */
