/**
 * @file STORAGE/jsonstorage.cpp
 *
 * @brief Le fichier header de gestion de l'import et l'export au format JSon des informations du programme
 *
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include <string>
#include "LOGIC/gestioncontact.h"

/**
 * @brief Classe pour la gestion de l'import et l'export au format JSon des informations du programme
 */
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
