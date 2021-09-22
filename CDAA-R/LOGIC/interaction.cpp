/**
 * @file LOGIC/interaction.cpp
 * @brief Classe pour une intéraction
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 22/09/2021
 */
#include "interaction.h"
#include "horodatage.h"

/**
 * @brief Constructeur de la classe Interaction
 * @param[in] c     Le contenu de l'interaction
 */
Interaction::Interaction(std::string c)
{
    this->contenu = c;

    this->horodatage = Horodatage();
}

/**
 * @brief Retourne l'id
 * @return l'id
 */
int Interaction::GetId()
{
    return this->id;
}

/**
 * @brief Retourne le contenu de l'intéraction
 * @return le contenu de l'intéraction
 */
std::string Interaction::GetContenu()
{
    return this->contenu;
}

/**
 * @brief Remplace le contenu de l'intéraction
 * @param[in] c     Le nouveau contenu
 */
void Interaction::SetContenu(std::string c)
{
    this->contenu = c;
}
