/**
 * @file LOGIC/horodatage.cpp
 * @brief La classe de gestion de la date et l'heure lors d'une action
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 22/09/2021
 */

#include "horodatage.h"
#include <QDateTime>
#include <QDate>

/**
 * @brief Constructeur de la classe Horodatage avec la date et l'heure **en paramètres**
 * @param[in] j     Variable stockant le jour en **entier**
 * @param[in] m     Variable stockant le mois en **entier**
 * @param[in] a     Variable stockant l'année en **entier**
 * @param[in] heu   Variable stockant l'heure en **entier**
 * @param[in] min   Variable stockant les minutes en **entier**
 * @param[in] sec   Variable stockant les secondes en **entier**
 */
Horodatage::Horodatage(int j, int m, int a, int heu, int min, int sec)
{
    this->jour = j;
    this->mois = m;
    this->annee = a;
    this->heure = heu;
    this->minute = min;
    this->seconde = sec;
}

/**
 * @brief Constructeur de la classe Horodatage avec date et heure **automatique**
 */
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

/**
 * @brief Renvoie en chaine de caractère la date et l'heure de l'horodatage afin de le rendre affichable
 * @return Retourne la date et l'heure au format **dd/MM/yyyy hh:mm:ss** en chaine de caractère
 */
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

/**
 * @brief Getter de Jour
 * @return Retourne le jour en **entier**
 */
int Horodatage::GetJour()
{
    return this->jour;
}

/**
 * @brief Getter de Mois
 * @return Retourne le mois en **entier**
 */
int Horodatage::GetMois()
{
    return this->mois;
}

/**
 * @brief Getter d'Annee
 * @return Retourne l'annee en **entier**
 */
int Horodatage::GetAnnee()
{
    return this->annee;
}

/**
 * @brief Getter d'Heure
 * @return Retourne l'heure en **entier**
 */
int Horodatage::GetHeure()
{
    return this->heure;
}

/**
 * @brief Getter de Minutes
 * @return Retourne les minutes en **entier**
 */
int Horodatage::GetMinute()
{
    return this->minute;
}

/**
 * @brief Getter de Seconde
 * @return Retourne les secondes en **entier**
 */
int Horodatage::GetSeconde()
{
    return this->seconde;
}

/**
 * @brief Setter de Jour
 * @param[in] j     Variable que l'on assigne au Jour
 */
void Horodatage::SetJour(int j)
{
    this->jour = j;
}

/**
 * @brief Setter de Mois
 * @param[in] m     Variable que l'on assigne au Mois
 */
void Horodatage::SetMois(int m)
{
    this->mois = m;
}

/**
 * @brief Setter d'Annee
 * @param[in] a     Variable que l'on assigne à l'annee
 */
void Horodatage::SetAnnee(int a)
{
    this->annee = a;
}

/**
 * @brief Setter de l'Heure
 * @param[in] j     Variable que l'on assigne au l'Heure
 */
void Horodatage::SetHeure(int heu)
{
    this->heure = heu;
}

/**
 * @brief Setter des Minutes
 * @param[in] m     Variable que l'on assigne aux Minutes
 */
void Horodatage::SetMinute(int min)
{
    this->minute = min;
}

/**
 * @brief Setter de Secondes
 * @param[in] a     Variable que l'on assigne aux secondes
 */
void Horodatage::SetSeconde(int sec)
{
    this->seconde = sec;
}
