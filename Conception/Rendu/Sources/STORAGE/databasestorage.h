/**
 * @file STORAGE/databasestorage.h
 * @brief Fichier header pour la gestion de la base de données
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
#ifndef DATABASESTORAGE_H
#define DATABASESTORAGE_H

#include <LOGIC/fichecontact.h>
#include <LOGIC/gestioncontact.h>

#include <string>

/**
 * @brief Classe pour la gestion de la base de données
 *
 * Cette classe permet de gèrer les entrées/sorties de l'application au niveau de la base de données.
 * Elle initialise donc la connexion avec elle et permet d'effectuer les requêtes necessaires pour la fenêtre de requêtes, et la sauvegarde des données de l'application.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
class DatabaseStorage
{
    public:
        static void InitializeBDD();
        static void CloseBDD();

        static void CreateContact(FicheContact);
        static Interaction CreateInteractionAndTags(std::string, std::string, Horodatage, int);
        static void CreateLog(std::string);

        static void UpdateContact(FicheContact);
        static void UpdateInteractionAndTags(Interaction);

        static void DeleteContact(FicheContact);
        static void DeleteInteractionAndTags(Interaction);

        static GestionContact Load();
        static void ReinitializeBDD(GestionContact);
        static std::vector<std::vector<std::string>> Request(std::string);
};

#endif // DATABASESTORAGE_H
