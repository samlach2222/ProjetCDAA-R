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
 * @author Samuel LACHAUD
 */
void SoundPlayer::PlayButtonSound()
{
    QSound::play(":/Ressources/Sounds/ButtonSound.wav");
}

/**
 * @brief Méthode pour jouer le son de l'erreur
 * @author Samuel LACHAUD
 */
void SoundPlayer::PlayErrorSound()
{
    QSound::play(":/Ressources/Sounds/ErrorSound.wav");
}
