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
        //Getters & Setters
        int getId() const;
        const std::string &getNom() const;
        void setNom(const std::string &newNom);
        const std::string &getPrenom() const;
        void setPrenom(const std::string &newPrenom);
        const std::string &getEntreprise() const;
        void setEntreprise(const std::string &newEntreprise);
        const std::string &getMail() const;
        void setMail(const std::string &newMail);
        const std::string &getTelephone() const;
        void setTelephone(const std::string &newTelephone);
        const QImage &getPhoto() const;
        void setPhoto(const QImage &newPhoto);
        const Horodatage &getDateCreation() const;
        std::vector<Interaction> &getListInteraction();

        FicheContact(int, std::string, std::string, std::string, std::string, std::string, QImage, Horodatage);
        void AddInteraction(std::string, std::string, Horodatage = Horodatage());
        void RemoveInteraction(int);
        std::string ToString();
};
#endif // FICHECONTACT_H
