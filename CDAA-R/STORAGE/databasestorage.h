/**
 * @file STORAGE/databasestorage.h
 * @brief Fichier header pour la gestion de la base de données
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
#ifndef DATABASESTORAGE_H
#define DATABASESTORAGE_H
#include "LOGIC/fichecontact.h"
#include "LOGIC/gestioncontact.h"
#include <string>

class DatabaseStorage
{
    public:
        static void Create(FicheContact c);
        static void Update(FicheContact c);
        static void Delete(int id);
        static GestionContact Load();
        static std::string Request(std::string sqlRequest);
};

#endif // DATABASESTORAGE_H