#ifndef DATABASESTORAGE_H
#define DATABASESTORAGE_H
#include "LOGIC/fichecontact.h"
#include "LOGIC/gestioncontact.h"
#include <string>

class DatabaseStorage
{
    public:
        DatabaseStorage();
        void Create(FicheContact c);
        void Update(FicheContact c);
        void Delete(FicheContact c);
        GestionContact Load();
        std::string Request(std::string sqlRequest);
};

#endif // DATABASESTORAGE_H
