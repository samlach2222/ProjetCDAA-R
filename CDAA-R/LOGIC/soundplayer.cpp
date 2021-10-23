/**
 * @file LOGIC/log.cpp
 * @brief Contient les méthode pour les sons de l'aplication
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 06/10/2021
 */

#include "soundplayer.h"

#include <QSound>

/**
 * @brief Méthode pour jouer le son du bouton standard
 */
void SoundPlayer::PlayButtonSound()
{
    QSound::play(":/Ressources/Sounds/ButtonSound.wav");
}

/**
 * @brief Méthode pour jouer le son du bouton alternatif
 */
void SoundPlayer::PlayButtonSound2()
{
    QSound::play(":/Ressources/Sounds/ButtonSound2.wav");
}

/**
 * @brief Méthode pour jouer le son de l'erreur
 */
void SoundPlayer::PlayErrorSound()
{
    QSound::play(":/Ressources/Sounds/ErrorSound.wav");
}
