/**
 * @file LOGIC/interaction.h
 * @brief Fichier header pour une interaction
 * @author Samuel LACHAUD
 * @author Samuel LACHAUD
 */
#ifndef INTERACTION_H
#define INTERACTION_H

#include "horodatage.h"
#include "tagsinteraction.h"

#include <string>

/**
 * @brief Classe pour une interaction
 *
 * Cette classe gère les interactions d'un contact. Une interaction sera donc créée ici avec ses différents attributs.
 * Les tags présents dans le contenu de l'interactions seront donc égalements gérées.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
class Interaction
{
    private:
        int id;
        std::string titre;
        std::string contenu;
        Horodatage dateCreation;
        tagsInteraction tags;
    public:
        int getId() const;
        const std::string &getTitre() const;
        void setTitre(const std::string &newTitre);
        const std::string &getContenu() const;
        void setContenu(const std::string &newContenu);
        const Horodatage &getDateCreation() const;
        const tagsInteraction &getTags() const;

        Interaction(int, std::string, std::string, Horodatage);
        void UpdateTags();
};

#endif // INTERACTION_H
