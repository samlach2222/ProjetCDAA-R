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
 * @author Samuel LACHAUD
 */
int Horodatage::getJour() const
{
    return jour;
}

/**
 * @brief Setter de Jour
 * @param[in] newJour     Variable que l'on assigne au Jour
 * @author Samuel LACHAUD
 */
void Horodatage::setJour(int newJour)
{
    jour = newJour;
}

/**
 * @brief Getter de Mois
 * @return Retourne le mois en **entier**
 * @author Samuel LACHAUD
 */
int Horodatage::getMois() const
{
    return mois;
}

/**
 * @brief Setter de Mois
 * @param[in] newMois     Variable que l'on assigne au Mois
 * @author Samuel LACHAUD
 */
void Horodatage::setMois(int newMois)
{
    mois = newMois;
}

/**
 * @brief Getter d'Annee
 * @return Retourne l'annee en **entier**
 * @author Samuel LACHAUD
 */
int Horodatage::getAnnee() const
{
    return annee;
}

/**
 * @brief Setter d'Annee
 * @param[in] newAnnee     Variable que l'on assigne à l'annee
 * @author Samuel LACHAUD
 */
void Horodatage::setAnnee(int newAnnee)
{
    annee = newAnnee;
}

/**
 * @brief Getter d'Heure
 * @return Retourne l'heure en **entier**
 * @author Samuel LACHAUD
 */
int Horodatage::getHeure() const
{
    return heure;
}

/**
 * @brief Setter de l'Heure
 * @param[in] newHeure     Variable que l'on assigne au l'Heure
 * @author Samuel LACHAUD
 */
void Horodatage::setHeure(int newHeure)
{
    heure = newHeure;
}

/**
 * @brief Getter de Minutes
 * @return Retourne les minutes en **entier**
 * @author Samuel LACHAUD
 */
int Horodatage::getMinute() const
{
    return minute;
}

/**
 * @brief Setter des Minutes
 * @param[in] newMinute     Variable que l'on assigne aux Minutes
 * @author Samuel LACHAUD
 */
void Horodatage::setMinute(int newMinute)
{
    minute = newMinute;
}

/**
 * @brief Getter de Seconde
 * @return Retourne les secondes en **entier**
 * @author Samuel LACHAUD
 */
int Horodatage::getSeconde() const
{
    return seconde;
}

/**
 * @brief Setter de Secondes
 * @param[in] newSeconde     Variable que l'on assigne aux secondes
 * @author Samuel LACHAUD
 */
void Horodatage::setSeconde(int newSeconde)
{
    seconde = newSeconde;
}

/**
 * @brief Constructeur de la classe Horodatage avec la date et l'heure **en paramètres**
 * @author Samuel LACHAUD
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
 *
 * Constructeur de la classe Horodatage, sans paramètres.
 * La date et l'heure sont fixées sur l'horloge système
 * @author Loïs PAZOLA
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
 * @author Samuel LACHAUD
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
 *
 * Retourne en chaine de caractère la date et l'heure de la classe horodatage sous le format "yyyy-MM-dd hh:mm:ss" pour l'utiliser dans la base de données.
 * @author Loïs PAZOLA
 * @return Retourne la date et l'heure au format **yyyy-MM-dd hh:mm:ss** en chaine de caractère
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

/**
 * @brief Renvoie en chaine de caractère la date et l'heure de l'horodatage afin de le rendre affichable pour les logs
 *
 * Retourne en chaine de caractère la date et l'heure de la classe horodatage sous le format "dd/MM/yyyy hh:mm:ss" pour l'afficher dans les logs.
 * @author Samuel LACHAUD
 * @return Retourne la date et l'heure au format **dd/MM/yyyy hh:mm:ss** en chaine de caractère
 */
std::string Horodatage::ToStringShowLog() const
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
