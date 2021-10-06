/**
 * @file LOGIC/horodatage.cpp
 *
 * @brief Le fichier header pour la gestion du temps et de l'heure d'une action
 *
 * @author Samuel LACHAUD
 */
#ifndef HORODATAGE_H
#define HORODATAGE_H

#include <string>

/**
 * @brief La classe pour la gestion du temps et de l'heure d'une action
 */
class Horodatage
{
    private:
        int jour;
        int mois;
        int annee;
        int heure;
        int minute;
        int seconde;
    public:
        Horodatage(int, int, int, int, int, int);
        Horodatage();
        Horodatage(std::string);
        std::string ToString();
        int GetJour();
        int GetMois();
        int GetAnnee();
        int GetHeure();
        int GetMinute();
        int GetSeconde();

        void SetJour(int);
        void SetMois(int);
        void SetAnnee(int);
        void SetHeure(int);
        void SetMinute(int);
        void SetSeconde(int);

};

#endif // HORODATAGE_H
