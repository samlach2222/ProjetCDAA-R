/**
 * @file STORAGE/jsonstorage.cpp
 * @brief La classe de gestion de l'import et l'export au format JSon des informations du programme
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 22/09/2021
 */

#include "jsonstorage.h"

/**
 * @brief Constructeur de la classe JSonStorage
 * @param[in] filename      Nom du fichier dans lequel va être sauvegardé les informations du programme **au format JSon**
 */
JSonStorage::JSonStorage(std::string filename)
{
    this->file = filename;
}

/**
 * @brief Permet de sauvegarder l'ensemble des contacts **gc** dans le fichier Json afin **d'assurer l'interopérabilité**
 * @param[in] gc    Ensemble des contacts de l'application
 * @todo METHODE A ECRIRE
 */
void JSonStorage::Save(GestionContact gc)
{
    //TODO
}

/**
 * @brief Permer de Charger depuis le fichier Json toutes les informations des contacts afin **d'assurer l'interopérabilité**
 * @return Retourne l'ensemble des informations de contacts sauvegardées
 * @todo METHODE A ECRIRE
 */
GestionContact JSonStorage::Load()
{
    //TODO
}

