/**
 * @file STORAGE/databasestorage.cpp
 * @brief Classe pour la gestion de la base de données
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 22/09/2021
 */
#include "databasestorage.h"

#include <QtSql>

/**
 * @brief Fonction constante qui renvoie une base de données \p QSqlDatabase initialisé
 * @return une base de données \p QSqlDatabase initialisé
 */
static const QSqlDatabase GetBDD(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("ConnexionDB");  //Nom de la connexion, à ne pas confondre avec...
    db.setDatabaseName("ContactDB");  //..Nom de la base de données
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()){
        throw std::runtime_error("La connexion à la base de données à échoué");
    }


    return db;
}

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
