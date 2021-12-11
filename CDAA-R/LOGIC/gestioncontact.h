/**
 * @file LOGIC/gestioncontact.h
 *
 * @brief Fichier Header pour la gestion des contacts de l'application
 *
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
#ifndef GESTIONCONTACT_H
#define GESTIONCONTACT_H

#include "fichecontact.h"
#include "horodatage.h"
#include "log.h"

#include <QImage>
#include <string>
#include <vector>

/**
 * @brief Classe pour la gestion des contacts de l'application
 *
 * Cette classe est un peu le coeur de l'application elle gère les différents contacts qui la compose.
 * Les différentes méthodes qui servent à les ajouter, supprimer ou modifier sont donc ici.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
class GestionContact
{
    private:
        std::vector<FicheContact> TabContacts;
        Log log;
    public:
        const std::vector<FicheContact> &GetAllContacts() const;
        Log &getLog();

        GestionContact(std::vector<FicheContact> = std::vector<FicheContact>(), Log = Log());
        void AddContact(std::string, std::string, std::string, std::string, std::string, QImage, Horodatage = Horodatage());
        void SupprContact(int);
        void ModifyContact(FicheContact);
        FicheContact &GetContact(int);
};

#endif // GESTIONCONTACT_H
