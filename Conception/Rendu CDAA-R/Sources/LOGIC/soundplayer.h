/**
 * @file LOGIC/soundplayer.h
 *
 * @brief Fichier Header pour la gestion des sons et musiques de l'application
 *
 * @author Samuel LACHAUD
 */
#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

/**
 * @brief Classe pour la gestion des sons de l'application
 *
 * Cette classe sert à gérer les différents bruitages de l'application.
 * Les sons de chaques clics sur des boutons de l'applications seront alors jouées ici, idem pour le son des messages d'erreurs.
 * @author Samuel LACHAUD
 */
class SoundPlayer
{
public:
    static void PlayButtonSound();
    static void PlayErrorSound();
};

#endif // SOUNDPLAYER_H
