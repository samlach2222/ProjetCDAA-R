/**
 * @file LOGIC/tagsInteraction.cpp
 * @brief Contient le tableau pour gèrer les tags des interactions
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 06/10/2021
 */

#include "tagsinteraction.h"

/**
 * @brief retourne le tableaux des couple (todo et date)
 * @return tableau de couple todo date
 * @author Samuel LACHAUD
 */
const std::vector<std::tuple<std::string, std::string> > &tagsInteraction::getTags() const
{
    return tags;
}

/**
 * @brief Remplace le vecteur de tuple de tags
 * @param[in] newTags   Nouveau tags
 * @author Samuel LACHAUD
 */
void tagsInteraction::setTags(const std::vector<std::tuple<std::string, std::string> > &newTags)
{
    tags = newTags;
}

/**
 * @brief Constructeur de la classe de gestion des tags d'interaction
 * @author Samuel LACHAUD
 */
tagsInteraction::tagsInteraction()
{
    this->tags = std::vector<std::tuple<std::string, std::string>>();
}

/**
 * @brief Méthode pour ajouter les tags d'une ligne dans le tableau
 * @author Samuel LACHAUD
 * @param[in] todo  chaine de caractère liée au [At]todo
 * @param[in] date  chaine de caractère liée au [At]date
 */
void tagsInteraction::addTag(std::string todo, std::string date)
{
    std::tuple<std::string, std::string> tuple = std::tuple<std::string, std::string>(todo, date);
    this->tags.push_back(tuple);
}
