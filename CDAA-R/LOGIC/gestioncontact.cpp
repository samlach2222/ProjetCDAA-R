/**
 * @file LOGIC/gestioncontact.cpp
 * @brief La classe de gestion de liste des Contacts
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.2
 * @date 08/10/2021
 */

#include "gestioncontact.h"
#include "STORAGE/databasestorage.h"

/**
 * @brief Constructeur de la classe
 */
GestionContact::GestionContact()
{
    this->TabContacts = std::vector<FicheContact>();
    this->log = Log();
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
            //Exemple : si idContacts contient 0,1,2,4,5 alors lorsque sortedIndex sera 4, le if testera si 4 != 2 + 1 et puisque c'est vrai renvoyer l'id 2 + 1
            firstAvailableId = lastId + 1;
            break;
        }

        lastId = sortedId;
    }

    FicheContact c = FicheContact(firstAvailableId, nom, prenom, entreprise, mail, telephone, photo, dateCreation);

    this->TabContacts.push_back(c);
    // sort here By ID
    DatabaseStorage::Create(c);
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
        DatabaseStorage::Delete(id);
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
            DatabaseStorage::Update(c);
            this->log.AddToTabLog("Contact Modified");
        }
    }
}

/**
 * @brief Permet de retourner tout les contacts
 * @return Retourne un tableau avec tout les contacts de l'application
 */
std::vector<FicheContact> GestionContact::GetAllContacts()
{
    return this->TabContacts;
}

/**
 * @brief Permet de récupérer le contact à partir de son identifiant **id**
 * @param[in] id    Identifiant du contact que l'on veux récupérer dans la liste
 * @return Retourne le contact qui a pour **id** le paramètre
 */
FicheContact GestionContact::GetContact(int id)
{
    FicheContact c = FicheContact(NULL, "", "", "", "", "", QImage(), Horodatage());
    for (int index = 0; index < static_cast<int>(this->TabContacts.size()); index++){
        if (this->TabContacts[index].getId() == id){
            c = this->TabContacts[index];
        }
    }
    return c;
}

/**
 * @brief Getter de Log
 * @return Retourne la classe Log instanciée
 */
Log &GestionContact::GetLog()
{
    return log;
}
