#ifndef MEDIA_PLAYER_HPP
#define MEDIA_PLAYER_HPP

#include <string>
#include <QMediaPlayer>
#include <QAudioOutput>

class MediaPlayer
{
public:
    MediaPlayer();
    ~MediaPlayer();

    std::string playSound(std::string filename, int repeatCount) const;
    void stop() const;

private:
    std::string play() const;

private:
    QMediaPlayer* mediaPlayer;
    QAudioOutput* audioOutput;
};

#endif // MEDIA_PLAYER_HPP
