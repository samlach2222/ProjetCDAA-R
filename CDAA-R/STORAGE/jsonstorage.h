/**
 * @file STORAGE/jsonstorage.cpp
 *
 * @brief Le fichier header pour la sauvegarde des informations en fichier JSON
 *
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include <string>
#include "LOGIC/gestioncontact.h"

class JSonStorage
{
    private:
        std::string filepath;
    public:
        JSonStorage(std::string filepath);
        void Save(GestionContact gc);
        GestionContact Load();
};

#endif // JSONSTORAGE_H
