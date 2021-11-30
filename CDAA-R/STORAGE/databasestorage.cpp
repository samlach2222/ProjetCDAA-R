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
void DatabaseStorage::InitializeBDD(){
    const QString nomBdd = "FakeDB.db";  //Nom du fichier de base de données à utiliser
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    //Si la base de données n'est pas présente, copie celui des ressources
    if (!QFileInfo::exists(nomBdd)){
        QFile fichierBddRessources(":/Ressources/Database/FakeDB.db");

        fichierBddRessources.copy(nomBdd);
    }

    db.setDatabaseName(nomBdd);  //Nom de la base de données

    if (!db.open()){
        throw db.lastError();
    }
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
    std::vector<FicheContact> tabContacts = std::vector<FicheContact>();

    QSqlQuery query("SELECT logsValue from LOGS");

    if (!query.exec()){
        //La base de données ne peut pas être accédé donc GestionContact est vide
        return GestionContact();
    }

    std::vector<std::string> logs;
    while (query.next()){
        logs.push_back(query.value(0).toString().toStdString());
    }

    //Boucle pour chaque contact
    query = QSqlQuery("SELECT * from CONTACT");
    while (query.next()){
        int id = query.value(0).toInt();
        std::string nom = query.value(1).toString().toStdString();
        std::string prenom = query.value(2).toString().toStdString();
        std::string entreprise = query.value(3).toString().toStdString();
        std::string mail = query.value(4).toString().toStdString();
        std::string telephone = query.value(5).toString().toStdString();

        //photo
        QImage photo;
        photo.loadFromData(query.value(6).toByteArray());

        //creationDate
        Horodatage creationDate = Horodatage(query.value(7).toString().toStdString());

        FicheContact fc = FicheContact(id, nom, prenom, entreprise, mail, telephone, photo, creationDate);

        //Boucle pour chaque interaction du contact
        std::vector<Interaction> interactions = std::vector<Interaction>();
        QSqlQuery queryInteractions = QSqlQuery("SELECT * from INTERACTION WHERE contactId = "+QString::number(id));
        while (queryInteractions.next()){
            int idInteraction = queryInteractions.value(0).toInt();
            std::string titreInteraction = queryInteractions.value(1).toString().toStdString();
            std::string contenuInteraction = queryInteractions.value(2).toString().toStdString();
            Horodatage horodatage = Horodatage(queryInteractions.value(3).toString().toStdString());

            Interaction interaction = Interaction(idInteraction, contenuInteraction, titreInteraction, horodatage);
            interactions.push_back(interaction);
        }
        fc.setListInteraction(interactions);

        //Ajoute le contact à tabContacts
        tabContacts.push_back(fc);
    }

    //Convertie le vecteur de string en un Log
    Log log = Log();
    log.setTabLog(logs);

    return GestionContact(tabContacts, log);
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
