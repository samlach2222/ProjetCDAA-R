/**
 * @file STORAGE/databasestorage.cpp
 * @brief Classe pour la gestion de la base de données
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 22/09/2021
 */

#include "databasestorage.h"

#include "../LOGIC/horodatage.h"

#include <QImage>
#include <QtSql>
#include <QVariant>

/**
 * @brief Fonction constante qui renvoie une base de données \p QSqlDatabase initialisé
 * @return une base de données \p QSqlDatabase initialisé
 */
static const QSqlDatabase GetBDD(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");  //Nom de l'host
    db.setDatabaseName("ContactDB");  //Nom de la base de données
    //db.setUserName("root");
    //db.setPassword("root");

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
    GestionContact gc = GestionContact();
    QSqlQuery query("SELECT logsValue from LOGS");

    if (!query.exec()){
        //La base de données ne peut pas être accédé donc GestionContact est vide
        return gc;
    }
    else {
        std::vector<std::string> logs;
        while (query.next()){
            logs.push_back(query.value(0).toString().toStdString());
        }

        query = QSqlQuery("SELECT * from CONTACT");
        while (query.next()){
            int idFC = query.value(0).toInt();
            std::string nom = query.value(1).toString().toStdString();
            std::string prenom = query.value(2).toString().toStdString();
            std::string entreprise = query.value(3).toString().toStdString();
            std::string mail = query.value(4).toString().toStdString();
            std::string telephone = query.value(5).toString().toStdString();

            //photo
            QImage photo;
            //QByteArray baPhoto = query.value(6).toByteArray();
            //photo.loadFromData(baPhoto);
            photo.loadFromData(query.value(6).toByteArray());

            //creationDate
            Horodatage creationDate = Horodatage(query.value(7).toString().toStdString());

            //Créer un FicheContact avec GestionContact, puis ajouter les interactions en utilisant idFC

        }



        //Doit être fait à la fin
        gc.getLog().setTabLog(logs);
    }

    return gc;
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
