/**
 * @file LOGIC/interaction.cpp
 * @brief Classe pour une intéraction
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.1
 * @date 01/10/2021
 */
#include "interaction.h"
//#include "horodatage.h"

/**
 * @brief Constructeur de la classe Interaction
 * @param[in] id        L'id de l'interaction
 * @param[in] c     Le contenu de l'interaction
 * @param[in] titre     Le titre de l'interaction
 * @param[in] horodatage        L'horodatage de l'interaction
 */
Interaction::Interaction(int id, std::string c, std::string titre, Horodatage horodatage)
{
    this->SetContenu(c);
    this->id = id;
    this->horodatage = horodatage;
    this->titre = titre;
    this->tags = tagsInteraction();
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

/**
 * @brief Retourne l'horodatage de l'interaction
 * @return l'horodatage de l'interaction
 */
Horodatage Interaction::GetHorodatage()
{
    return this->horodatage;
}

/**
 * @brief Retourne le titre de l'interaction
 * @return le titre de l'interaction
 */
std::string Interaction::getTitre()
{
    return this->titre;
}

/**
 * @brief Remplace le titre de l'interaction
 * @param[in] titre     Le nouveau titre
 */
void Interaction::setTitre(std::string titre)
{
    this->titre = titre;
}

/**
 * @brief Permet de récupérer les tags d'un intéraction
 * @return classe des tags d'intéraction
 */
tagsInteraction Interaction::getTags()
{
    return this->tags;
}

/**
 * @brief Permet de changer la valeur des tags d'une intéraction
 * @param[in] tags d'une intéraction
 */
void Interaction::setTags(tagsInteraction tags)
{
    this->tags = tags;
}
