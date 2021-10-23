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
 */
class GestionContact
{
    private:
        std::vector<FicheContact> TabContacts;
        Log log;
    public:
        GestionContact();
        void AddContact(std::string, std::string, std::string, std::string, std::string, QImage, Horodatage = Horodatage());
        void SupprContact(int);
        void ModifyContact(FicheContact);
        std::vector<FicheContact> GetAllContacts();
        FicheContact GetContact(int);
        Log &GetLog();
};

#endif // GESTIONCONTACT_H
