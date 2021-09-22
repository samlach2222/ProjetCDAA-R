#include "gestioncontact.h"
#include "STORAGE/databasestorage.h"



GestionContact::GestionContact()
{
    this->TabContacts = std::vector<FicheContact>();
    this->log = Log();
}

void GestionContact::AddContact(FicheContact c)
{
    this->TabContacts.push_back(c);
    DatabaseStorage::Create(c);
    this->log.AddToTabLog("Contact Added");
}

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

std::vector<FicheContact> GestionContact::GetAllContacts()
{
    return this->TabContacts;
}

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

Log GestionContact::getLog()
{
    return log;
}
