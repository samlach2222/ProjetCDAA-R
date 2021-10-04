/**
 * @file STORAGE/jsonstorage.cpp
 * @brief La classe de gestion de l'import et l'export au format JSon des informations du programme
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.2
 * @date 22/09/2021
 */

#include "jsonstorage.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QBuffer>
#include <QStandardPaths>
#include <QDir>
#include <QTextStream>

/**
 * @brief Constructeur de la classe JSonStorage
 * @param[in] filepath      Nom et chemin du fichier dans lequel va être sauvegardé les informations du programme **au format JSon**
 */
JSonStorage::JSonStorage(std::string filepath)
{
    this->filepath = filepath;
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
    std::vector<std::string> tabLog = gc.GetLog().getTabLog();
    foreach (std::string logStr, tabLog){
        json["log"+QString::number(id)] = QString::fromStdString(logStr);

        id++;
    }
    json["logTotal"] = id;

    //contacts
    id = 0;
    foreach(FicheContact fc, gc.GetAllContacts()){
        json["contact"+QString::number(id)+"id"] = fc.getId();
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

        id++;
    }
    json["contactTotal"] = id;

    QJsonDocument json_doc(json);
    QString json_string = json_doc.toJson();

    //Création du dossier %AppData%/CDAA-R
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir appDataDir(appDataPath);
    if (!appDataDir.exists()){
        appDataDir.mkpath(".");
    }

    QFile file(QString::fromStdString(this->filepath));
    file.open(QIODevice::WriteOnly);
    file.write(json_string.toLocal8Bit());
    file.close();
}

/**
 * @brief Permer de charger depuis le fichier JSon toutes les informations des contacts et des logs afin **d'assurer l'interopérabilité**
 * @return Retourne l'ensemble des informations des contacts et des logs sauvegardées
 */
GestionContact JSonStorage::Load()
{
    GestionContact gc = GestionContact();

    //Lecture du fichier de sauvegarde
    QFile file(QString::fromStdString(this->filepath));
    if(!file.open(QIODevice::ReadOnly)){
        //Quitte prématurément si le fichier n'existe pas
        return gc;
    }
    QTextStream fileText(&file);
    QString jsonText = fileText.readAll();
    file.close();

    //Conversion en QJsonObject
    QByteArray jsonData = jsonText.toLocal8Bit();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    QJsonObject json = jsonDoc.object();

    for (int cId = 0; cId < json["contactTotal"].toInt(); cId++){
        int id = json["contact"+QString::number(cId)+"id"].toInt();
        std::string nom = json["contact"+QString::number(cId)+"nom"].toString().toStdString();
        std::string prenom = json["contact"+QString::number(cId)+"prenom"].toString().toStdString();
        std::string entreprise = json["contact"+QString::number(cId)+"entreprise"].toString().toStdString();
        std::string mail = json["contact"+QString::number(cId)+"mail"].toString().toStdString();
        std::string telephone = json["contact"+QString::number(cId)+"telephone"].toString().toStdString();

        std::string strDateCreation = json["contact"+QString::number(cId)+"dateCreation"].toString().toStdString();
        Horodatage dateCreation = Horodatage(strDateCreation);

        //Conversion du base64 en QImage
        QString b64str = json["contact"+QString::number(id)+"photo"].toString();
        QByteArray b64ba = b64str.toLocal8Bit();
        QImage photo;
        photo.loadFromData(QByteArray::fromBase64(b64ba));

        gc.AddContact(nom, prenom, entreprise, mail, telephone, photo, dateCreation);
    }

    std::vector<std::string> logs;
    for (int Lid = 0; Lid < json["logTotal"].toInt(); Lid++){
        std::string log = json["log"+QString::number(Lid)].toString().toStdString();
        logs.push_back(log);
    }
    gc.GetLog().SetTabLog(logs);

    return gc;
}

