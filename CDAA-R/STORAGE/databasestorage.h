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
 */
class DatabaseStorage
{
    public:
        static void InitializeBDD();

        static void Create(FicheContact);
        static void Update(FicheContact);
        static void Delete(int);
        static GestionContact Load();
        static std::string Request(std::string);
};

#endif // DATABASESTORAGE_H
