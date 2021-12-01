/**
 * @file LOGIC/horodatage.cpp
 * @brief La classe de gestion de la date et l'heure lors d'une action
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 22/09/2021
 */

#include "horodatage.h"

#include <QDateTime>
#include <QString>

/**
 * @brief Getter de Jour
 * @return Retourne le jour en **entier**
 */
int Horodatage::getJour() const
{
    return jour;
}

/**
 * @brief Setter de Jour
 * @param[in] newJour     Variable que l'on assigne au Jour
 */
void Horodatage::setJour(int newJour)
{
    jour = newJour;
}

/**
 * @brief Getter de Mois
 * @return Retourne le mois en **entier**
 */
int Horodatage::getMois() const
{
    return mois;
}

/**
 * @brief Setter de Mois
 * @param[in] newMois     Variable que l'on assigne au Mois
 */
void Horodatage::setMois(int newMois)
{
    mois = newMois;
}

/**
 * @brief Getter d'Annee
 * @return Retourne l'annee en **entier**
 */
int Horodatage::getAnnee() const
{
    return annee;
}

/**
 * @brief Setter d'Annee
 * @param[in] newAnnee     Variable que l'on assigne à l'annee
 */
void Horodatage::setAnnee(int newAnnee)
{
    annee = newAnnee;
}

/**
 * @brief Getter d'Heure
 * @return Retourne l'heure en **entier**
 */
int Horodatage::getHeure() const
{
    return heure;
}

/**
 * @brief Setter de l'Heure
 * @param[in] newHeure     Variable que l'on assigne au l'Heure
 */
void Horodatage::setHeure(int newHeure)
{
    heure = newHeure;
}

/**
 * @brief Getter de Minutes
 * @return Retourne les minutes en **entier**
 */
int Horodatage::getMinute() const
{
    return minute;
}

/**
 * @brief Setter des Minutes
 * @param[in] newMinute     Variable que l'on assigne aux Minutes
 */
void Horodatage::setMinute(int newMinute)
{
    minute = newMinute;
}

/**
 * @brief Getter de Seconde
 * @return Retourne les secondes en **entier**
 */
int Horodatage::getSeconde() const
{
    return seconde;
}

/**
 * @brief Setter de Secondes
 * @param[in] newSeconde     Variable que l'on assigne aux secondes
 */
void Horodatage::setSeconde(int newSeconde)
{
    seconde = newSeconde;
}

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
    this->setJour(j);
    this->setMois(m);
    this->setAnnee(a);
    this->setHeure(heu);
    this->setMinute(min);
    this->setSeconde(sec);
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

    this->setJour(date.day());
    this->setMois(date.month());
    this->setAnnee(date.year());

    this->setHeure(time.hour());
    this->setMinute(time.minute());
    this->setSeconde(time.second());
}

/**
 * @brief Constructeur de la classe Horodatage à partir d'un string généré par le \p ToString()
 * @param[in] strDate       La date sous forme de string qui sera convertie
 */
Horodatage::Horodatage(std::string strDate)
{
    QDateTime dt = QDateTime::fromString(QString::fromStdString(strDate), "yyyy-MM-dd hh:mm:ss");
    QDate date = dt.date();
    QTime time = dt.time();

    this->setJour(date.day());
    this->setMois(date.month());
    this->setAnnee(date.year());

    this->setHeure(time.hour());
    this->setMinute(time.minute());
    this->setSeconde(time.second());
}

/**
 * @brief Renvoie en chaine de caractère la date et l'heure de l'horodatage afin de le rendre affichable
 * @return Retourne la date et l'heure au format **dd/MM/yyyy hh:mm:ss** en chaine de caractère
 */
std::string Horodatage::ToString() const
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
    return datetime.toString("yyyy-MM-dd hh:mm:ss").toStdString();
}
