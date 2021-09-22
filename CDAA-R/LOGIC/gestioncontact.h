#ifndef GESTIONCONTACT_H
#define GESTIONCONTACT_H
#include "fichecontact.h"
#include "log.h"
#include <vector>

class GestionContact
{
    private:
        std::vector<FicheContact> TabContacts;
        Log log;
    public:
        GestionContact();
        void AddContact(FicheContact c);
        void SupprContact(int id);
        void ModifyContact(FicheContact c);
        std::vector<FicheContact> GetAllContacts();
        FicheContact GetContact(int id);
};

#endif // GESTIONCONTACT_H
