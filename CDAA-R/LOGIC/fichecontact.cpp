#include "fichecontact.h"
#include "horodatage.h"

FicheContact::FicheContact(std::string nom, std::string prenom, std::string entreprise, std::string mail, std::string telephone, QImage photo)
{
    this->id = 0;  //TODO: récupérer le plus grand id unique
    this->nom = nom;
    this->prenom = prenom;
    this->entreprise = entreprise;
    this->mail = mail;
    this->telephone = telephone;
    this->photo = photo;
    this->dateCreation = Horodatage();
}

int FicheContact::getId()
{
    return id;
}

std::string FicheContact::getNom()
{
    return nom;
}

void FicheContact::setNom(std::string newNom)
{
    nom = newNom;
}

std::string FicheContact::getPrenom()
{
    return prenom;
}

void FicheContact::setPrenom(std::string newPrenom)
{
    prenom = newPrenom;
}

std::string FicheContact::getEntreprise()
{
    return entreprise;
}

void FicheContact::setEntreprise(std::string newEntreprise)
{
    entreprise = newEntreprise;
}

std::string FicheContact::getMail()
{
    return mail;
}

void FicheContact::setMail(std::string newMail)
{
    mail = newMail;
}

std::string FicheContact::getTelephone()
{
    return telephone;
}

void FicheContact::setTelephone(std::string newTelephone)
{
    telephone = newTelephone;
}

QImage FicheContact::getPhoto()
{
    return photo;
}

void FicheContact::setPhoto(QImage newPhoto)
{
    photo = newPhoto;
}

Horodatage FicheContact::getDateCreation()
{
    return dateCreation;
}

void FicheContact::setDateCreation(Horodatage newDateCreation)
{
    dateCreation = newDateCreation;
}

std::vector<Interaction> FicheContact::GetListInteraction()
{
    return listInteraction;
}

void FicheContact::AddInteraction(Interaction i)
{
    listInteraction.push_back(i);
}

void FicheContact::RemoveInteraction(int id)
{
    std::vector<int> indexInteractionsASupprimer;

    for (int index = 0; index < static_cast<int>(listInteraction.size()); index++){
        if (listInteraction[index].GetId() == id){
            indexInteractionsASupprimer.push_back(index);
        }
    }

    int decalage = 0;
    for (int& index: indexInteractionsASupprimer){
        listInteraction.erase(listInteraction.begin() + index - decalage);

        decalage++;
    }

    //listInteraction.erase (std::remove_if(listInteraction.begin(), listInteraction.end(), [&](Interaction currentI){return currentI == i;}));
}

std::string FicheContact::ToString()
{
    return nom + " " + prenom;
}
