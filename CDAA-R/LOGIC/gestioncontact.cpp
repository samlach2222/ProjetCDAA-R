#include "gestioncontact.h"

GestionContact::GestionContact()
{
    this->TabContacts = std::vector<FicheContact>();
}

void GestionContact::AddContact(FicheContact c)
{
    this->TabContacts.push_back(c);
}

void GestionContact::SupprContact(int id)
{

}
