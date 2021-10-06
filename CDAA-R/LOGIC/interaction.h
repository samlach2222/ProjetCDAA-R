/**
 * @file LOGIC/interaction.h
 * @brief Fichier header pour une intéraction
 * @author Samuel LACHAUD
 */
#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include "horodatage.h"

/**
 * @brief Classe pour une intéraction
 */
class Interaction
{
    private:
        int id;
        std::string titre;
        std::string contenu;
        Horodatage horodatage;
    public:
        Interaction(int id, std::string, std::string);
        int GetId();
        std::string GetContenu();
        void SetContenu(std::string);
        Horodatage GetHorodatage();
        std::string getTitre();
        void setTitre(std::string);
};

#endif // INTERACTION_H
