/**
 * @file STORAGE/databasestorage.cpp
 * @brief Classe pour la gestion de la base de données
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.1
 * @date 22/09/2021
 */

#include "databasestorage.h"

#include <LOGIC/horodatage.h>

#include <QImage>
#include <QtSql>
#include <QVariant>

/**
 * @brief Initialise la base de données
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
 */
void DatabaseStorage::CreateContact(FicheContact c)
{
    QString strQuery = "INSERT INTO CONTACT(contactFirstName, contactLastName, contactEntreprise, contactMail, contactMail, contactPhone, contactPicture, contactCreationDate) ";
    strQuery += "VALUES(:firstName, :lastName, :entreprise, :mail, :phone, :picture, :creationDate)";
    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(":firstName", QString::fromStdString(c.getPrenom()));
    query.bindValue(":lastName", QString::fromStdString(c.getNom()));
    query.bindValue(":entreprise", QString::fromStdString(c.getEntreprise()));
    query.bindValue(":mail", QString::fromStdString(c.getMail()));
    query.bindValue(":phone", QString::fromStdString(c.getTelephone()));

    QImage photo = c.getPhoto();
    QByteArray ba;
    QBuffer buf(&ba);
    buf.open(QIODevice::WriteOnly);
    photo.save(&buf, "PNG");
    QByteArray ba2 = ba.toBase64();
    buf.close();
    QString b64str = QString::fromLatin1(ba2);

    query.bindValue(":picture", b64str);
    query.bindValue(":creationDate", QString::fromStdString(c.getDateCreation().ToString()));
    query.exec();
}

/**
 * @brief Créé une interaction et ses tags associés dans la base de données
 * @param i     Interaction à ajouter
 * @param contactId     id du contact auquel appartiens l'interaction
 */
void DatabaseStorage::CreateInteractionAndTags(Interaction i, int contactId)
{
    QString strQuery = "INSERT INTO INTERACTION(interactionTitle, interactionContent, interactionDate, contactId) "; // mise à jour d'interaction
    strQuery += "VALUES(:interactionTitle, :interactionContent, :interactionDate, :id)";
    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(":id", i.getId());
    query.bindValue(":interactionTitle", QString::fromStdString(i.getTitre()));
    query.bindValue(":interactionContent", QString::fromStdString(i.getContenu()));
    query.bindValue(":interactionDate", QString::fromStdString(i.getDateCreation().ToString()));
    query.bindValue(":id", contactId);
    query.exec();

    tagsInteraction t = i.getTags(); // ajout des tags associés
    for(std::tuple<std::string, std::string> tuple : t.getTags()){
        strQuery = "INSERT INTO TAGS (tagTodo, tagDate, interactionId) ";
        strQuery = "VALUES(:todo, :date, :id)";
        query.prepare(strQuery);
        query.bindValue(":todo", QString::fromStdString(get<0>(tuple)));
        query.bindValue(":date", QString::fromStdString(get<1>(tuple)));
        query.bindValue(":id", i.getId());
        query.exec();
    }
}

void DatabaseStorage::CreateLog(std::string l)
{
    QString strQuery = "INSERT INTO LOGS(logsValue) "; // mise à jour d'interaction
    strQuery += "VALUES(:logsValue)";
    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(":logsValue", QString::fromStdString(l));
    query.exec();
}

/**
 * @brief Met à jour une FicheContact dans la base de données
 * @param[in] c     La nouvelle FicheContact
 */
void DatabaseStorage::UpdateContact(FicheContact c)
{
    QString strQuery = "UPDATE CONTACT ";
    strQuery += "SET(:firstName, :lastName, :entreprise, :mail, :phone, :picture, :creationDate) ";
    strQuery += "WHERE contactId = :id";
    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(":id", c.getId());
    query.bindValue(":firstName", QString::fromStdString(c.getPrenom()));
    query.bindValue(":lastName", QString::fromStdString(c.getNom()));
    query.bindValue(":entreprise", QString::fromStdString(c.getEntreprise()));
    query.bindValue(":mail", QString::fromStdString(c.getMail()));
    query.bindValue(":phone", QString::fromStdString(c.getTelephone()));

    QImage photo = c.getPhoto();
    QByteArray ba;
    QBuffer buf(&ba);
    buf.open(QIODevice::WriteOnly);
    photo.save(&buf, "PNG");
    QByteArray ba2 = ba.toBase64();
    buf.close();
    QString b64str = QString::fromLatin1(ba2);

    query.bindValue(":picture", b64str);
    query.bindValue(":creationDate", QString::fromStdString(c.getDateCreation().ToString()));
    query.exec();
}

/**
 * @brief Met à jour une Interaction dans la base de données
 * @param[in] i     La nouvelle Interaction
 */
void DatabaseStorage::UpdateInteractionAndTags(Interaction i)
{
    QString strQuery = "UPDATE INTERACTION "; // mise à jour d'interaction
    strQuery += "SET(:interactionTitle, :interactionContent, :interactionDate) ";
    strQuery += "WHERE interactionId = :id";
    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(":id", i.getId());
    query.bindValue(":interactionTitle", QString::fromStdString(i.getTitre()));
    query.bindValue(":interactionContent", QString::fromStdString(i.getContenu()));
    query.bindValue(":interactionDate", QString::fromStdString(i.getDateCreation().ToString()));
    query.exec();

    strQuery = "DELETE FROM TAGS"; // suppression des tags associés
    strQuery += "WHERE interactionId = :id";
    query.prepare(strQuery);
    query.bindValue(":id", i.getId());
    query.exec();

    tagsInteraction t = i.getTags(); // recréation des tags associés
    for(std::tuple<std::string, std::string> tuple : t.getTags()){
        strQuery = "INSERT INTO TAGS (tagTodo, tagDate, interactionId) ";
        strQuery = "VALUES(:todo, :date, :id)";
        query.prepare(strQuery);
        query.bindValue(":todo", QString::fromStdString(get<0>(tuple)));
        query.bindValue(":date", QString::fromStdString(get<1>(tuple)));
        query.bindValue(":id", i.getId());
        query.exec();
    }
}

/**
 * @brief Supprime une FicheContact dans la base de données
 * @param[in] c     Le contact à supprimer
 */
void DatabaseStorage::DeleteContact(FicheContact c)
{
    QString strQuery = "DELETE FROM CONTACT ";
    strQuery += "WHERE contactId = :id";
    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(":id", c.getId());

    query.exec();
}

/**
 * @brief Supprime une Interaction et ses tags dans la base de données
 * @param[in] i     l'interaction à supprimer
 */
void DatabaseStorage::DeleteInteractionAndTags(Interaction i)
{
    QString strQuery = "DELETE FROM INTERACTION ";
    strQuery += "WHERE interactionId = :id";
    QSqlQuery query;
    query.prepare(strQuery);
    query.bindValue(":id", i.getId());
    query.exec();

    strQuery = "DELETE FROM TAGS";
    strQuery += "WHERE interactionId = :id";
    query.prepare(strQuery);
    query.bindValue(":id", i.getId());
    query.exec();
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
        Horodatage creationDate = Horodatage(query.value(7).toString().toStdString());

        //photo
        QImage photo;
        photo.loadFromData(QByteArray::fromBase64(query.value(6).toString().toLocal8Bit()));

        FicheContact fc = FicheContact(id, nom, prenom, entreprise, mail, telephone, photo, creationDate);

        //Boucle pour chaque interaction du contact
        std::vector<Interaction> interactions = std::vector<Interaction>();
        QSqlQuery queryInteractions;
        queryInteractions.prepare("SELECT * from INTERACTION WHERE contactId = :id");
        queryInteractions.bindValue(":id", id);
        queryInteractions.exec();
        while (queryInteractions.next()){
            int idInteraction = queryInteractions.value(0).toInt();
            std::string titreInteraction = queryInteractions.value(1).toString().toStdString();
            std::string contenuInteraction = queryInteractions.value(2).toString().toStdString();
            Horodatage dateCreationInteraction = Horodatage(queryInteractions.value(3).toString().toStdString());

            Interaction interaction = Interaction(idInteraction, contenuInteraction, titreInteraction, dateCreationInteraction);
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
 * @return le résultat sous forme de string pour chaque valeur, pour chaque ligne de résultat
 */
std::vector<std::vector<std::string>> DatabaseStorage::Request(std::string sqlRequest)
{
    std::vector<std::vector<std::string>> resultats = std::vector<std::vector<std::string>>();
    QSqlQuery query(QString::fromStdString(sqlRequest));

    //Pour chaque ligne de résultat de la requête
    while(query.next()){
        //Ajoute chaque valeur dans un vector de string...
        std::vector<std::string> ligneResultat = std::vector<std::string>();
        for (int idValue = 0; idValue < query.record().count(); idValue++){
            ligneResultat.push_back(query.value(idValue).toString().toStdString());
        }

        //....Puis ajoute ce vector au vector principal contenant les valeurs de chaque ligne
        resultats.push_back(ligneResultat);
    }

    return resultats;
}
