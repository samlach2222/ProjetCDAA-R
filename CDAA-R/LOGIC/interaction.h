/**
 * @file LOGIC/interaction.h
 * @brief Fichier header pour une intéraction
 * @author Samuel LACHAUD
 */
#ifndef INTERACTION_H
#define INTERACTION_H
#include <string>
#include "horodatage.h"

class Interaction
{
    private:
        int id;
        std::string contenu;
        Horodatage horodatage;
    public:
        Interaction(std::string c, int id);
        int GetId();
        std::string GetContenu();
        void SetContenu(std::string c);
};

#endif // INTERACTION_H
