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
Interaction::Interaction(int id, std::string c, std::string titre, Horodatage horodatage)
{
    this->SetContenu(c);
    this->id = id;
    this->horodatage = horodatage;
    this->titre = titre;
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
 * @brief Remplace le contenu de l'intéraction et met à jour les tags
 * @param[in] c     Le nouveau contenu
 */
void Interaction::SetContenu(std::string c)
{
    this->contenu = c;

    tagsInteraction tags = tagsInteraction();
    QStringList text_in_lines = QString::fromStdString(c).split( "\n" );
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

                tags.addTag(tagTodo,strDate);
            }
            else // cas où il y a un tag TODO mais pas de tag DATE
            {
                int firstDelPos = currentLine.find("@todo");
                std::string tagTodo = currentLine.substr(firstDelPos+6);
                std::string strDate = QDate::currentDate().toString("dd/MM/yyyy").toStdString();

                tags.addTag(tagTodo,strDate);
            }
        }
    }
    this->setTags(tags);
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
