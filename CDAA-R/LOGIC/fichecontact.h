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
    public:
        FicheContact(std::string nom, std::string prenom, std::string entreprise, std::string mail, std::string telephone, QImage photo);

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
        void setDateCreation(Horodatage newDateCreation);

        std::vector<Interaction> GetListInteraction();
        void AddInteraction(Interaction i);
        void RemoveInteraction(int id);
        std::string ToString();
};

#endif // FICHECONTACT_H
