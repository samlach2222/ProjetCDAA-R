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
        Horodatage(int j, int m, int a, int heu, int min, int sec);
        Horodatage();
        Horodatage(std::string strDate);
        std::string ToString();
        int GetJour();
        int GetMois();
        int GetAnnee();
        int GetHeure();
        int GetMinute();
        int GetSeconde();

        void SetJour(int j);
        void SetMois(int m);
        void SetAnnee(int a);
        void SetHeure(int heu);
        void SetMinute(int min);
        void SetSeconde(int sec);

};

#endif // HORODATAGE_H
