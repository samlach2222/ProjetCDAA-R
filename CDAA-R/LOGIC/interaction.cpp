#include "interaction.h"
#include "horodatage.h"

Interaction::Interaction(std::string c)
{
    this->contenu = c;

    this->horodatage = Horodatage();
}

int Interaction::GetId()
{
    return this->id;
}

std::string Interaction::GetContenu()
{
    return this->contenu;
}

void Interaction::SetContenu(std::string c)
{
    this->contenu = c;
}
