/**
 * @file LOGIC/fichecontact.h
 * @brief Fichier header pour les détails d'un contact et ses interactions
 * @author Loïs PAZOLA
 */
#ifndef FICHECONTACT_H
#define FICHECONTACT_H
#include <string>
#include <QImage>
#include <vector>
#include "horodatage.h"
#include "interaction.h"

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
        Horodatage dateCreation;
        std::vector<Interaction> listInteraction;

        int interactionHighestId;
    public:
        FicheContact(int id, std::string nom, std::string prenom, std::string entreprise, std::string mail, std::string telephone, QImage photo, Horodatage horodatage);
        //Getters & Setters
        int getId();
        std::string getNom();
        void setNom(std::string newNom);
        std::string getPrenom();
        void setPrenom(std::string newPrenom);
        std::string getEntreprise();
        void setEntreprise(std::string newEntreprise);
        std::string getMail();
        void setMail(std::string newMail);
        std::string getTelephone();
        void setTelephone(std::string newTelephone);
        QImage getPhoto();
        void setPhoto(QImage newPhoto);
        Horodatage getDateCreation();

        std::vector<Interaction> GetListInteraction();
        void AddInteraction(std::string contenuInteraction);
        void RemoveInteraction(int id);
        std::string ToString();
};
#endif // FICHECONTACT_H
