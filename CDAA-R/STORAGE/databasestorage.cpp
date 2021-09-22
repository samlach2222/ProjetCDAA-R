/**
 * @file STORAGE/databasestorage.cpp
 * @brief Classe pour la gestion de la base de données
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 22/09/2021
 */
#include "databasestorage.h"

/**
 * @brief Créé une FicheContact dans la base de données
 * @param[in] c     La FicheContact à créé dans la base de données
 * @todo MÉTHODE À ÉCRIRE
 */
void DatabaseStorage::Create(FicheContact c)
{
    //TODO
}

/**
 * @brief Met à jour une FicheContact dans la base de données
 * @param[in] c     La nouvelle FicheContact
 * @todo MÉTHODE À ÉCRIRE
 */
void DatabaseStorage::Update(FicheContact c)
{
    //TODO: Utilise l'id
}

/**
 * @brief Supprime une FicheContact dans la base de données
 * @param[in] id        L'id de la FicheContact à supprimer
 * @todo MÉTHODE À ÉCRIRE
 */
void DatabaseStorage::Delete(int id)
{
    //TODO
}

/**
 * @brief Retourne une GestionContact à partir de la base de données
 * @return une GestionContact à partir de la base de données
 * @todo MÉTHODE À ÉCRIRE
 */
GestionContact DatabaseStorage::Load()
{
    //TODO
}

/**
 * @brief Envoie la requête sql \p sqlRequest et retourne le résultat
 * @param[in] sqlRequest        La requête sql
 * @return le résultat de la requête
 * @todo MÉTHODE À ÉCRIRE
 */
std::string DatabaseStorage::Request(std::string sqlRequest)
{
    //TODO
}
