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
        int getJour() const;
        void setJour(int newJour);
        int getMois() const;
        void setMois(int newMois);
        int getAnnee() const;
        void setAnnee(int newAnnee);
        int getHeure() const;
        void setHeure(int newHeure);
        int getMinute() const;
        void setMinute(int newMinute);
        int getSeconde() const;
        void setSeconde(int newSeconde);

        Horodatage(int, int, int, int, int, int);
        Horodatage();
        Horodatage(std::string);
        std::string ToString() const;
};

#endif // HORODATAGE_H
