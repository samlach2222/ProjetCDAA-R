/**
 * @file LOGIC/interaction.cpp
 * @brief Classe pour une intéraction
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.1
 * @date 01/10/2021
 */

#include "interaction.h"

/**
 * @brief Constructeur de la classe Interaction
 * @param[in] id        L'id de l'interaction
 * @param[in] c     Le contenu de l'interaction
 * @param[in] titre     Le titre de l'interaction
 * @param[in] horodatage        L'horodatage de l'interaction
 */

/**
 * @brief Retourne l'id
 * @return l'id
 */
int Interaction::getId() const
{
    return id;
}

/**
 * @brief Retourne le titre de l'interaction
 * @return le titre de l'interaction
 */
const std::string &Interaction::getTitre() const
{
    return titre;
}

/**
 * @brief Remplace le titre de l'interaction
 * @param[in] titre     Le nouveau titre
 */
void Interaction::setTitre(const std::string &newTitre)
{
    titre = newTitre;
}

/**
 * @brief Retourne le contenu de l'intéraction
 * @return le contenu de l'intéraction
 */
const std::string &Interaction::getContenu() const
{
    return contenu;
}

/**
 * @brief Remplace le contenu de l'intéraction et met à jour les tags
 * @param[in] c     Le nouveau contenu
 */
void Interaction::setContenu(const std::string &newContenu)
{
    contenu = newContenu;
}

/**
 * @brief Retourne l'horodatage de l'interaction
 * @return l'horodatage de l'interaction
 */
const Horodatage &Interaction::getHorodatage() const
{
    return horodatage;
}

/**
 * @brief Permet de récupérer les tags d'un intéraction
 * @return classe des tags d'intéraction
 */
const tagsInteraction &Interaction::getTags() const
{
    return tags;
}

Interaction::Interaction(int id, std::string c, std::string titre, Horodatage horodatage)
{
    this->setContenu(c);
    this->id = id;
    this->horodatage = horodatage;
    this->titre = titre;
}

/**
 * @brief Met à jour les tags de l'interaction
 */
void Interaction::UpdateTags()
{
    tagsInteraction newTags = tagsInteraction();
    QStringList text_in_lines = QString::fromStdString(this->contenu).split('\n');
    for( int j = 0; j < text_in_lines.count(); j++ )
    {
        std::string currentLine = text_in_lines.at( j ).toStdString();
        if(((int) currentLine.find("@todo")) != -1)
        {
            if(((int) currentLine.find("@date")) != -1) // cas où il y a un tag TODO puis un tag DATE
            {
                int firstDelPos = currentLine.find("@todo");
                int secondDelPos = currentLine.find("@date");
                std::string tagTodo = currentLine.substr(firstDelPos+6, secondDelPos-firstDelPos-7);
                std::string strDate = currentLine.substr(secondDelPos+6);

                newTags.addTag(tagTodo,strDate);
            }
            else // cas où il y a un tag TODO mais pas de tag DATE
            {
                int firstDelPos = currentLine.find("@todo");
                std::string tagTodo = currentLine.substr(firstDelPos+6);
                std::string strDate = QDate::currentDate().toString("dd/MM/yyyy").toStdString();

                newTags.addTag(tagTodo,strDate);
            }
        }
    }

    this->tags = newTags;
}
