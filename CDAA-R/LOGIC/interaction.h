/**
 * @file LOGIC/interaction.h
 * @brief Fichier header pour une intéraction
 * @author Samuel LACHAUD
 * @author Samuel LACHAUD
 */
#ifndef INTERACTION_H
#define INTERACTION_H

#include "horodatage.h"
#include "tagsinteraction.h"

#include <string>

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
        tagsInteraction tags;
    public:
        Interaction(int, std::string, std::string, Horodatage);
        int GetId();
        std::string GetContenu();
        void SetContenu(std::string);
        Horodatage GetHorodatage();
        std::string getTitre();
        void setTitre(std::string);
        tagsInteraction getTags();
        void UpdateTags();
};

#endif // INTERACTION_H
