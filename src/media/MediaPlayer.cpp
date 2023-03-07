#include "media/MediaPlayer.hpp"

MediaPlayer::MediaPlayer()
{
    mediaPlayer = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    audioOutput->setVolume(100);
    mediaPlayer->setAudioOutput(audioOutput);
}

MediaPlayer::~MediaPlayer()
{
    if (mediaPlayer)
        mediaPlayer->deleteLater();
    if (audioOutput)
        audioOutput->deleteLater();
}

std::string MediaPlayer::playSound(std::string filename, int repeatCount) const
{
    mediaPlayer->setSource(QUrl::fromLocalFile(filename.c_str()));
    mediaPlayer->setLoops(repeatCount);
    return play();
}

std::string MediaPlayer::play() const
{
    if (mediaPlayer)
    {
        mediaPlayer->play();
        return mediaPlayer->errorString().toStdString();
    }
    return "";
}

void MediaPlayer::stop() const
{
    if (mediaPlayer)
        mediaPlayer->stop();
}
