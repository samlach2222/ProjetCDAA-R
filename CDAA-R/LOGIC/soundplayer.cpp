#include "soundplayer.h"
#include <QSound>

void SoundPlayer::PlayButtonSound()
{
    QSound::play(":/Ressources/Sounds/ButtonSound.wav");
}

void SoundPlayer::PlayButtonSound2()
{
    QSound::play(":/Ressources/Sounds/ButtonSound2.wav");
}

void SoundPlayer::PlayErrorSound()
{
    QSound::play(":/Ressources/Sounds/ErrorSound.wav");
}
