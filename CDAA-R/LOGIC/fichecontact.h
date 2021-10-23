/**
 * @file LOGIC/fichecontact.h
 * @brief Fichier header pour les détails d'un contact et ses interactions
 * @author Loïs PAZOLA
 */
#ifndef FICHECONTACT_H
#define FICHECONTACT_H

#include "horodatage.h"
#include "interaction.h"

#include <QImage>
#include <string>
#include <vector>

/**
 * @brief Classe pour les détails d'un contact et ses interactions
 */
class FicheContact
{
    private:
        int id;  //Readonly
        std::string nom;
        std::string prenom;
        std::string entreprise;
        std::string mail;
        std::string telephone;
        QImage photo;
        Horodatage dateCreation;  //Readonly
        std::vector<Interaction> listInteraction;
    public:
        FicheContact(int, std::string, std::string, std::string, std::string, std::string, QImage, Horodatage);
        //Getters & Setters
        int getId();
        std::string getNom();
        void setNom(std::string);
        std::string getPrenom();
        void setPrenom(std::string);
        std::string getEntreprise();
        void setEntreprise(std::string);
        std::string getMail();
        void setMail(std::string);
        std::string getTelephone();
        void setTelephone(std::string);
        QImage getPhoto();
        void setPhoto(QImage);
        Horodatage getDateCreation();

        std::vector<Interaction> GetListInteraction();
        void AddInteraction(std::string, std::string, Horodatage = Horodatage());
        void RemoveInteraction(int);
        std::string ToString();
};
#endif // FICHECONTACT_H
