#ifndef GESTIONCONTACT_H
#define GESTIONCONTACT_H
#include "fichecontact.h"
#include <vector>

class GestionContact
{
    private:
        std::vector<FicheContact> TabContacts;
    public:
        GestionContact();
        void AddContact(FicheContact c);
        void SupprContact(int id);
        void ModifyContact(int id);
        std::vector<FicheContact> GetAllContacts();
        FicheContact GetContact(int id);
};

#endif // GESTIONCONTACT_H
