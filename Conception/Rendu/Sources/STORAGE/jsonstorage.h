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

#include <LOGIC/gestioncontact.h>

/**
 * @brief Classe pour la gestion de l'import et l'export au format JSon des informations du programme
 */
class JSonStorage
{
    public:
        static void Save(GestionContact);
        static GestionContact Load();
};

#endif // JSONSTORAGE_H
