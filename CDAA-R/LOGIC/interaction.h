#ifndef INTERACTION_H
#define INTERACTION_H
#include <string>
#include "horodatage.h"

class Interaction
{
    private:
        int id;
        std::string contenu;
        Horodatage horodatage;
    public:
        Interaction(std::string c);
        int GetId();
        std::string GetContenu();
        void SetContenu(std::string c);
};

#endif // INTERACTION_H
