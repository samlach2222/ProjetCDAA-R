#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H
#include <QtMultimedia/QMediaPlayer>

class SoundPlayer
{
public:
    static void PlayButtonSound();
    static void PlayButtonSound2();
    static void PlayErrorSound();
};

#endif // SOUNDPLAYER_H
