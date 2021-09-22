#include "horodatage.h"
#include <QDateTime>
#include <QDate>

Horodatage::Horodatage(int j, int m, int a, int heu, int min, int sec)
{
    this->jour = j;
    this->mois = m;
    this->annee = a;
    this->heure = heu;
    this->minute = min;
    this->seconde = sec;
}

Horodatage::Horodatage()
{
    QDateTime dt;
    dt = dt.currentDateTime();
    QDate date = dt.date();
    QTime time = dt.time();

    this->jour = date.day();
    this->mois = date.month();
    this->annee = date.year();

    this->heure = time.hour();
    this->minute = time.minute();
    this->seconde = time.second();
}

std::string Horodatage::ToString()
{
    // On définit la date
    QDate date;
    date.setDate(this->annee, this->mois, this->jour);

    // On définit l'heure
    QTime time;
    time.setHMS(this->heure, this->minute, this->seconde);

    // On regroupe dans un datetime
    QDateTime datetime;
    datetime.setDate(date);
    datetime.setTime(time);

    // on retourne en std::string
    return datetime.toString("dd/MM/yyyy hh:mm:ss").toStdString();
}

int Horodatage::GetJour()
{
    return this->jour;
}
int Horodatage::GetMois()
{
    return this->mois;
}
int Horodatage::GetAnnee()
{
    return this->annee;
}
void Horodatage::SetJour(int j)
{
    this->jour = j;
}
void Horodatage::SetMois(int m)
{
    this->mois = m;
}
void Horodatage::SetAnnee(int a)
{
    this->annee = a;
}
