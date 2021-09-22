/**
 * @file LOGIC/gestioncontact.cpp
 * @brief La classe de gestion de liste des Contacts
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 22/09/2021
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
 * @brief Permet d'ajouter un contact **c** à la liste de contacts
 * @param[in] c     Contact à ajouter à la liste
 */
void GestionContact::AddContact(FicheContact c)
{
    this->TabContacts.push_back(c);
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
        DatabaseStorage::Delete(this->GetContact(id));
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
    FicheContact c = FicheContact("","","","","",QImage());
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
Log GestionContact::getLog()
{
    return log;
}
