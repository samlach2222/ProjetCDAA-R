#ifndef HORODATAGE_H
#define HORODATAGE_H
#include <string>
#include <QDateTime>


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
        std::string ToString();
        int GetJour();
        int GetMois();
        int GetAnnee();
        void SetJour(int j);
        void SetMois(int m);
        void SetAnnee(int a);
};

#endif // HORODATAGE_H
