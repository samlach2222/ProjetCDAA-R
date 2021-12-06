/**
 * @file LOGIC/gestioncontact.cpp
 * @brief La classe de gestion de liste des Contacts
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.2
 * @date 08/10/2021
 */

#include "gestioncontact.h"

#include <STORAGE/databasestorage.h>

/**
 * @brief Permet de retourner tout les contacts
 * @return Retourne un tableau avec tout les contacts de l'application
 */
const std::vector<FicheContact> &GestionContact::GetAllContacts() const
{
    return TabContacts;
}

/**
 * @brief Getter de Log
 * @return Retourne la classe Log instanciée
 */
Log &GestionContact::getLog()
{
    return log;
}

/**
 * @brief Constructeur de la classe
 * @param[in] tabContacts       Contacts de l'application
 * @param[in] log       Logs de l'application
 */
GestionContact::GestionContact(std::vector<FicheContact> tabContacts, Log log)
{
    this->TabContacts = tabContacts;
    this->log = log;
}

/**
 * @brief Permet de créer et ajouter un contact à la liste des contacts à partir des données passées en paramètres
 * @param[in] nom       Nom du contact
 * @param[in] prenom        Prénom du contact
 * @param[in] entreprise        Entreprise du contact
 * @param[in] mail      Mail du contact
 * @param[in] telephone     Numéro de téléphone du contact
 * @param[in] photo     Photo de profile du contact
 * @param[in] dateCreation      Date de création (**optionelle**)
 */
void GestionContact::AddContact(std::string nom, std::string prenom, std::string entreprise, std::string mail, std::string telephone, QImage photo, Horodatage dateCreation)
{
    std::vector<FicheContact> allContacts = GetAllContacts();
    int firstAvailableId = allContacts.size();

    std::vector<int> idContacts(allContacts.size());
    for (int index = 0; index < static_cast<int>(allContacts.size()); index++){
        idContacts[index] = allContacts[index].getId();
    }

    std::sort(idContacts.begin(), idContacts.end());
    int lastId = -1;
    foreach (int sortedId, idContacts){
        if (sortedId != lastId + 1){
            //Exemple : si idContacts contient 0,1,2,4,5 alors lorsque sortedId sera 4, le if testera si 4 != 2 + 1 et puisque c'est vrai renvoyer l'id 2 + 1
            firstAvailableId = lastId + 1;
            break;  // on sort du foreach si l'élément est trouvé (économie de performence)
        }

        lastId = sortedId;
    }

    FicheContact c = FicheContact(firstAvailableId, nom, prenom, entreprise, mail, telephone, photo, dateCreation);

    this->TabContacts.push_back(c);
    DatabaseStorage::CreateContact(c);
    this->log.AddToTabLog("Contact Added");
}

/**
 * @brief Permet de supprimer un contact par son **id** de la liste de contacts
 * @param[in] id    Identifiant du contact à supprimer
 */
void GestionContact::SupprContact(int id)
{
    std::vector<int> indexContactASupprimer;

    for (int index = 0; index < static_cast<int>(this->TabContacts.size()); index++){
        if (this->TabContacts[index].getId() == id){
            indexContactASupprimer.push_back(index);
        }
    }

    int decalage = 0;
    for (int& index: indexContactASupprimer){
        FicheContact c = this->GetContact(id);
        DatabaseStorage::DeleteContact(c);
        this->TabContacts.erase(this->TabContacts.begin() + index - decalage);
        this->log.AddToTabLog("Contact Removed");

        decalage++;
    }
}

/**
 * @brief Permet de modifier un contact en le remplacant par un contact **c**
 * @param[in] c     Contact qu'on modifie dans la liste des contacts
 */
void GestionContact::ModifyContact(FicheContact c)
{
    int id = c.getId();

    for (int index = 0; index < static_cast<int>(this->TabContacts.size()); index++){
        if (this->TabContacts[index].getId() == id){
            this->TabContacts.at(index) = c;
            DatabaseStorage::UpdateContact(c);
            this->log.AddToTabLog("Contact Modified");
        }
    }
}

/**
 * @brief Permet de récupérer le contact à partir de son identifiant **id**
 * @param[in] id    Identifiant du contact que l'on veux récupérer dans la liste
 * @return le contact qui a pour **id** le paramètre
 * @throw std::invalid_argument Il n'y a aucun contact ayant l'id passé en paramètre
 */
FicheContact &GestionContact::GetContact(int id)
{
    for (int index = 0; index < static_cast<int>(this->TabContacts.size()); index++){
        if (this->TabContacts[index].getId() == id){
            return this->TabContacts[index];
        }
    }

    //Aucun contact ayant l'id recherché --> Erreur
#ifdef UWP
    exit(1);  //UWP ne supporte pas les throws
#else
    throw std::invalid_argument("Il n'y a aucun contact avec l'id "+std::to_string(id));
#endif
}
