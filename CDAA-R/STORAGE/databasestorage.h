#ifndef DATABASESTORAGE_H
#define DATABASESTORAGE_H
#include "LOGIC/fichecontact.h"
#include "LOGIC/gestioncontact.h"
#include <string>

class DatabaseStorage
{
    public:
        //static DatabaseStorage();
        static void Create(FicheContact c);
        static void Update(FicheContact c);
        static void Delete(FicheContact c);
        static GestionContact Load();
        static std::string Request(std::string sqlRequest);
};

#endif // DATABASESTORAGE_H
