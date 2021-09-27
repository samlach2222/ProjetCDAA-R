/**
 * @file STORAGE/jsonstorage.cpp
 * @brief La classe de gestion de l'import et l'export au format JSon des informations du programme
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 22/09/2021
 */

#include "jsonstorage.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QBuffer>
#include <QStandardPaths>
#include <QDir>

/**
 * @brief Constructeur de la classe JSonStorage
 * @param[in] filename      Nom et chemin du fichier dans lequel va être sauvegardé les informations du programme **au format JSon**
 */
JSonStorage::JSonStorage(std::string filename)
{
    this->file = filename;
}

/**
 * @brief Permet de sauvegarder l'ensemble des contacts et logs de **gc** dans le fichier JSon afin **d'assurer l'interopérabilité**
 * @param[in] gc    Ensemble des contacts de l'application
 */
void JSonStorage::Save(GestionContact gc)
{
    QJsonObject json;
    int id = 0;

    //log
    id = 0;
    Log log = gc.getLog();
    foreach (std::string logStr, log.getTabLog()){
        json["log"+QString::number(id)] = QString::fromStdString(logStr);

        id++;
    }

    //contacts
    id = 0;
    foreach(FicheContact fc, gc.GetAllContacts()){
        json["contact"+QString::number(id)+"id"] = QString::number(fc.getId());
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

    QJsonDocument json_doc(json);
    QString json_string = json_doc.toJson();

    //Création du dossier %AppData%/CDAA-R
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir appDataDir(appDataPath);
    if (!appDataDir.exists()){
        appDataDir.mkpath(".");
    }

    QFile file(QString::fromStdString(this->file));
    file.open(QIODevice::WriteOnly);
    file.write(json_string.toLocal8Bit());
    file.close();
}

/**
 * @brief Permer de Charger depuis le fichier JSon toutes les informations des contacts et des logs afin **d'assurer l'interopérabilité**
 * @return Retourne l'ensemble des informations des contacts et des logs sauvegardées
 * @todo METHODE A ECRIRE
 */
GestionContact JSonStorage::Load()
{
    //TODO
}

