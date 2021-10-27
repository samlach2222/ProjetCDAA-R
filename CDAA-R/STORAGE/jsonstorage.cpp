/**
 * @file STORAGE/jsonstorage.cpp
 * @brief La classe de gestion de l'import et l'export au format JSon des informations du programme
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.3
 * @date 22/09/2021
 */

#include "jsonstorage.h"

#include "../LOGIC/fichecontact.h"
#include "../LOGIC/horodatage.h"

#include <QBuffer>
#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QString>
#include <QTextStream>
#include <string>
#include <vector>

/**
 * @brief Retourne le chemin et nom du fichier de sauvegarde
 * @return le chemin et nom du fichier de sauvegarde
 */
static const QString GetFilepath(){
    //Ne peut pas être une variable globale constante car sinon donne le chemin %appdata%/Save.json
    //Ne peut pas être une fonction publique ou variable publique de la classe car sinon il faut créer une variable de type JSonStorage exprès pour (les méthodes static n'ont pas directement accès aux éléments de la classe), ni privé car les méthodes static n'y auraient pas accès du tout
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/Save.json";
}

/**
 * @brief Permet de sauvegarder l'ensemble des contacts et logs de **gc** dans le fichier JSon afin **d'assurer l'interopérabilité**
 * @param[in] gc        Ensemble des contacts et logs de l'application
 */
void JSonStorage::Save(GestionContact gc)
{
    QJsonObject json;
    int id = 0;

    //log
    id = 0;
    std::vector<std::string> tabLog = gc.getLog().getTabLog();
    foreach (std::string logStr, tabLog){
        json["log"+QString::number(id)] = QString::fromStdString(logStr);

        ++id;
    }
    json["logTotal"] = id;

    //contacts
    id = 0;
    foreach(FicheContact fc, gc.GetAllContacts()){
        //json["contact"+QString::number(id)+"id"] = fc.getId();
        json["contact"+QString::number(id)+"nom"] = QString::fromStdString(fc.getNom());
        json["contact"+QString::number(id)+"prenom"] = QString::fromStdString(fc.getPrenom());
        json["contact"+QString::number(id)+"entreprise"] = QString::fromStdString(fc.getEntreprise());
        json["contact"+QString::number(id)+"mail"] = QString::fromStdString(fc.getMail());
        json["contact"+QString::number(id)+"telephone"] = QString::fromStdString(fc.getTelephone());
        json["contact"+QString::number(id)+"dateCreation"] = QString::fromStdString(fc.getDateCreation().ToString());

        //photo
        QImage photo = fc.getPhoto();
        QByteArray ba;
        QBuffer buf(&ba);
        buf.open(QIODevice::WriteOnly);
        photo.save(&buf, "PNG");
        QByteArray ba2 = ba.toBase64();
        buf.close();
        QString b64str = QString::fromLatin1(ba2);
        json["contact"+QString::number(id)+"photo"] = b64str;

        //interactions
        int idInteraction = 0;
        foreach (Interaction i, fc.getListInteraction()){
            //json["contact"+QString::number(id)+"interaction"+QString::number(idInteraction)+"id"] = i.GetId();  //On a pas besoin d'exporter l'id
            json["contact"+QString::number(id)+"interaction"+QString::number(idInteraction)+"titre"] = QString::fromStdString(i.getTitre());
            json["contact"+QString::number(id)+"interaction"+QString::number(idInteraction)+"contenu"] = QString::fromStdString(i.GetContenu());
            json["contact"+QString::number(id)+"interaction"+QString::number(idInteraction)+"horodatage"] = QString::fromStdString(i.GetHorodatage().ToString());

            ++idInteraction;
        }
        json["contact"+QString::number(id)+"interactionTotal"] = idInteraction;


        ++id;
    }
    json["contactTotal"] = id;

    //QJsonDocument json_doc = QJsonDocument(json);
    //QString json_string = json_doc.toJson();
    QString json_string = QJsonDocument(json).toJson();

    //Création du dossier %AppData%/CDAA-R
    QDir appDataDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));  //Ne pas donner GetFilepath() car cela créerait un DOSSIER %appdata%/CDAA-R/Save.json/
    if (!appDataDir.exists()){
        appDataDir.mkpath(".");
    }

    QFile file(GetFilepath());
    file.open(QIODevice::WriteOnly);
    file.write(json_string.toUtf8());
    file.close();
}

/**
 * @brief Permer de charger depuis le fichier JSon toutes les informations des contacts et des logs afin **d'assurer l'interopérabilité**
 * @return l'ensemble des informations des contacts et des logs sauvegardées
 */
GestionContact JSonStorage::Load()
{
    GestionContact gc = GestionContact();

    //Lecture du fichier de sauvegarde
    QFile file(GetFilepath());
    if(!file.open(QIODevice::ReadOnly)){
        //Quitte prématurément si le fichier n'existe pas
        return gc;
    }
    QTextStream fileText(&file);
    QString jsonText = fileText.readAll();
    file.close();

    //Conversion en QJsonObject
    //QByteArray jsonData = jsonText.toLatin1();
    //QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    //QJsonObject json = jsonDoc.object();
    QJsonObject json = QJsonDocument::fromJson(jsonText.toLatin1()).object();

    for (int cId = 0; cId < json["contactTotal"].toInt(); ++cId){
        //int id = json["contact"+QString::number(cId)+"id"].toInt();  //On a pas besoin d'importer l'id
        std::string nom = json["contact"+QString::number(cId)+"nom"].toString().toStdString();
        std::string prenom = json["contact"+QString::number(cId)+"prenom"].toString().toStdString();
        std::string entreprise = json["contact"+QString::number(cId)+"entreprise"].toString().toStdString();
        std::string mail = json["contact"+QString::number(cId)+"mail"].toString().toStdString();
        std::string telephone = json["contact"+QString::number(cId)+"telephone"].toString().toStdString();

        //Conversion du string en Horodatage
        //std::string strDateCreation = json["contact"+QString::number(cId)+"dateCreation"].toString().toStdString();
        //Horodatage dateCreation = Horodatage(strDateCreation);
        Horodatage dateContact = Horodatage(json["contact"+QString::number(cId)+"dateCreation"].toString().toStdString());

        //Conversion du base64 en QImage
        QImage photo;
        //QString b64str = json["contact"+QString::number(id)+"photo"].toString();
        //QByteArray b64ba = b64str.toLocal8Bit();
        //photo.loadFromData(QByteArray::fromBase64(b64ba));
        photo.loadFromData(QByteArray::fromBase64(json["contact"+QString::number(cId)+"photo"].toString().toLocal8Bit()));

        //Ajout du contact
        gc.AddContact(nom, prenom, entreprise, mail, telephone, photo, dateContact);

        //Ajout des interactions du contact
        for (int iId = 0; iId < json["contact"+QString::number(cId)+"interactionTotal"].toInt(); ++iId){
            //int id = json["contact"+QString::number(cId)+"interaction"+QString::number(iId)+"id"].toInt();
            std::string titre = json["contact"+QString::number(cId)+"interaction"+QString::number(iId)+"titre"].toString().toStdString();
            std::string contenu = json["contact"+QString::number(cId)+"interaction"+QString::number(iId)+"contenu"].toString().toStdString();

            //Conversion du string en Horodatage
            //std::string strDateInteraction = json["contact"+QString::number(cId)+"interaction"+QString::number(iId)+"horodatage"].toString().toStdString();
            //Horodatage dateInteraction = Horodatage(strDateInteraction);
            Horodatage dateInteraction = Horodatage(json["contact"+QString::number(cId)+"interaction"+QString::number(iId)+"horodatage"].toString().toStdString());

            gc.GetContact(cId).AddInteraction(contenu, titre, dateInteraction);
        }
    }

    //Les logs doivent être importer à la fin
    std::vector<std::string> logs;
    for (int Lid = 0; Lid < json["logTotal"].toInt(); Lid++){
        std::string log = json["log"+QString::number(Lid)].toString().toStdString();
        logs.push_back(log);
    }
    gc.getLog().setTabLog(logs);

    return gc;
}
