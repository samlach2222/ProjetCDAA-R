/**
 * @file LOGIC/tagsInteraction.cpp
 * @brief Contient le tableau pour gèrer les tags des intéractions
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 06/10/2021
 */
#include "tagsinteraction.h"

/**
 * @brief Constructeur de la classe de gestion des tags d'intéraction
 */
tagsInteraction::tagsInteraction()
{
    this->tags = std::vector<std::tuple<std::string, std::string>>();
}

/**
 * @brief retourne le tableaux des couple (todo et date)
 * @return tableau de couple todo date
 */
std::vector<std::tuple<std::string, std::string>> tagsInteraction::getTags()
{
    return this->tags;
}

/**
 * @brief Interaction::setTags
 * @param tags
 */
void tagsInteraction::setTags(std::vector<std::tuple<std::string, std::string>> tags)
{
    this->tags = tags;
}

void tagsInteraction::addTag(std::string todo, std::string date)
{
    std::tuple<std::string, std::string> tuple = std::tuple<std::string, std::string>(todo, date);
    this->tags.push_back(tuple);
}

void tagsInteraction::resetTags()
{
    this->tags.clear();
}
