/**
 * @file LOGIC/interaction.cpp
 * @brief Classe pour une interaction
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.2
 * @date 01/10/2021
 */

#include "interaction.h"

#include <QDate>
#include <QString>
#include <QStringList>

/**
 * @brief Retourne l'id
 * @return l'id
 * @author Samuel LACHAUD
 */
int Interaction::getId() const
{
    return id;
}

/**
 * @brief Retourne le titre de l'interaction
 * @return le titre de l'interaction
 * @author Samuel LACHAUD
 */
const std::string &Interaction::getTitre() const
{
    return titre;
}

/**
 * @brief Remplace le titre de l'interaction
 * @param[in] newTitre     Le nouveau titre
 * @author Samuel LACHAUD
 */
void Interaction::setTitre(const std::string &newTitre)
{
    titre = newTitre;
}

/**
 * @brief Retourne le contenu de l'interaction
 * @return le contenu de l'interaction
 * @author Samuel LACHAUD
 */
const std::string &Interaction::getContenu() const
{
    return contenu;
}

/**
 * @brief Remplace le contenu de l'interaction et met à jour les tags
 * @param[in] newContenu     Le nouveau contenu
 * @author Samuel LACHAUD
 */
void Interaction::setContenu(const std::string &newContenu)
{
    contenu = newContenu;

    //Il faut mettre à jour les tags à chaque fois que le contenu est modifié
    UpdateTags();
}

/**
 * @brief Retourne la date de création de l'interaction
 * @return la date de création de l'interaction
 * @author Samuel LACHAUD
 */
const Horodatage &Interaction::getDateCreation() const
{
    return dateCreation;
}

/**
 * @brief Permet de récupérer les tags d'un interaction
 * @return classe des tags d'interaction
 * @author Samuel LACHAUD
 */
const tagsInteraction &Interaction::getTags() const
{
    return tags;
}

/**
 * @brief Constructeur de la classe Interaction
 * @author Samuel LACHAUD
 * @param[in] id        L'id de l'interaction
 * @param[in] c     Le contenu de l'interaction
 * @param[in] titre     Le titre de l'interaction
 * @param[in] dateCreation        La date de création de l'interaction
 */
Interaction::Interaction(int id, std::string c, std::string titre, Horodatage dateCreation)
{
    this->id = id;
    this->setContenu(c);
    this->titre = titre;
    this->dateCreation = dateCreation;
}

/**
 * @brief Met à jour les tags de l'interaction
 *
 * Met a jour les tags de l'interaction à partir du contenu. Les tags DATE et tags TODO sont alors actualisés.
 * @author Samuel LACHAUD
 */
void Interaction::UpdateTags()
{
    tagsInteraction newTags = tagsInteraction();
    const QStringList text_in_lines = QString::fromStdString(this->contenu).split('\n');
    for(int j = 0; j < text_in_lines.count(); j++)
    {
        const std::string currentLine = text_in_lines.at(j).toStdString();

        const size_t posTodo = currentLine.find("@todo");
        if(posTodo != std::string::npos)  //Si le tag @todo existe dans la ligne
        {
            const size_t posDate = currentLine.find("@date");
            if(posDate != std::string::npos && posDate > posTodo)  //Si le tag @date existe et se situe après le tag @todo
            {
                std::string strTodo = currentLine.substr(posTodo+6, posDate-posTodo-7);
                std::string strDate = currentLine.substr(posDate+6);

                newTags.addTag(strTodo,strDate);
            }
            else  //Cas où il y a un tag @todo mais pas de tag @date ou mal positionné
            {
                std::string strTodo = currentLine.substr(posTodo+6);
                std::string strDate = QDate::currentDate().toString("dd/MM/yyyy").toStdString();

                newTags.addTag(strTodo,strDate);
            }
        }
    }

    this->tags = newTags;
}
