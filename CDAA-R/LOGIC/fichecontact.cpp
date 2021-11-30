/**
 * @file LOGIC/fichecontact.cpp
 * @brief Contient les détails d'un contact et ses interactions
 * @author Loïs PAZOLA
 * @version 1.2
 * @date 04/10/2021
 */

#include "fichecontact.h"

/**
 * @brief Retourne l'id
 * @return l'id
 */
int FicheContact::getId() const
{
    return id;
}

/**
 * @brief Retourne le nom
 * @return le nom
 */
const std::string &FicheContact::getNom() const
{
    return nom;
}

/**
 * @brief Remplace le nom
 * @param[in] newNom        Le nouveau nom
 */
void FicheContact::setNom(const std::string &newNom)
{
    nom = newNom;
}

/**
 * @brief Retourne le prénom
 * @return le prénom
 */
const std::string &FicheContact::getPrenom() const
{
    return prenom;
}

/**
 * @brief Remplace le prénom
 * @param[in] newPrenom     Le nouveau prénom
 */
void FicheContact::setPrenom(const std::string &newPrenom)
{
    prenom = newPrenom;
}

/**
 * @brief Retourne l'entreprise
 * @return l'entreprise
 */
const std::string &FicheContact::getEntreprise() const
{
    return entreprise;
}

/**
 * @brief Remplace l'entreprise
 * @param[in] newEntreprise     La nouvelle entreprise
 */
void FicheContact::setEntreprise(const std::string &newEntreprise)
{
    entreprise = newEntreprise;
}

/**
 * @brief Retourne le mail
 * @return le mail
 */
const std::string &FicheContact::getMail() const
{
    return mail;
}

/**
 * @brief Remplace le mail
 * @param[in] newMail       Le nouveau mail
 */
void FicheContact::setMail(const std::string &newMail)
{
    mail = newMail;
}

/**
 * @brief Retourne le numéro de téléphone
 * @return le numéro de téléphone
 */
const std::string &FicheContact::getTelephone() const
{
    return telephone;
}

/**
 * @brief Remplace le numéro de téléphone
 * @param[in] newTelephone      Le nouveau numéro de téléphone
 */
void FicheContact::setTelephone(const std::string &newTelephone)
{
    telephone = newTelephone;
}

/**
 * @brief Retourne la photo de profil
 * @return la photo de profil
 */
const QImage &FicheContact::getPhoto() const
{
    return photo;
}

/**
 * @brief Remplace la photo de profil
 * @param[in] newPhoto      La nouvelle photo de profil
 */
void FicheContact::setPhoto(const QImage &newPhoto)
{
    photo = newPhoto;
}

/**
 * @brief Retourne la date de création de la fiche contact
 * @return la date de création de la fiche contact
 */
const Horodatage &FicheContact::getDateCreation() const
{
    return dateCreation;
}

/**
 * @brief Retourne la liste des intéractions du contact
 * @return la liste des interactions du contact
 */
std::vector<Interaction> &FicheContact::getListInteraction()
{
    return listInteraction;
}

/**
 * @brief Constructeur de la classe FicheContact
 * @param[in] id        L'id du contact
 * @param[in] nom       Nom du contact
 * @param[in] prenom        Prénom du contact
 * @param[in] entreprise        Entreprise du contact
 * @param[in] mail      Mail du contact
 * @param[in] telephone     Numéro de téléphone du contact
 * @param[in] photo     Photo de profile du contact
 * @param[in] dateCreation      Date de création
 */
FicheContact::FicheContact(int id, std::string nom, std::string prenom, std::string entreprise, std::string mail, std::string telephone, QImage photo, Horodatage dateCreation)
{
    this->id = id;
    this->setNom(nom);
    this->setPrenom(prenom);
    this->setEntreprise(entreprise);
    this->setMail(mail);
    this->setTelephone(telephone);
    this->setPhoto(photo);
    this->dateCreation = dateCreation;
}

/**
 * @brief Crée une interaction à partir d'un contenu passé en paramètre et l'ajoute à la liste des interactions
 * @param[in] contenuInteraction        Le contenu à partir duquel l'interaction sera créé
 * @param[in] titreInteraction        Le titre de l'interaction
 * @param[in] horodatage        L'horodatage de l'interaction (**optionelle**)
 */
void FicheContact::AddInteraction(std::string contenuInteraction, std::string titreInteraction, Horodatage horodatage)
{
    std::vector<Interaction> allInteractions = getListInteraction();
    int firstAvailableId = allInteractions.size();

    std::vector<int> idInteractions(allInteractions.size());
    for (int index = 0; index < static_cast<int>(allInteractions.size()); index++){
        idInteractions[index] = allInteractions[index].getId();
    }

    std::sort(idInteractions.begin(), idInteractions.end());
    int lastId = -1;
    foreach (int sortedId, idInteractions){
        if (sortedId != lastId + 1){
            //Exemple : si idInteractions contient 0,1,2,4,5 alors lorsque sortedId sera 4, le if testera si 4 != 2 + 1 et puisque c'est vrai renvoyer l'id 2 + 1
            firstAvailableId = lastId + 1;
            break;  // on sort du foreach si l'élément est trouvé (économie de performence)
        }

        lastId = sortedId;
    }

    Interaction i = Interaction(firstAvailableId, contenuInteraction, titreInteraction, horodatage);

    listInteraction.push_back(i);
}

/**
 * @brief Enlève l'interaction d'id \p id de la liste des interactions
 * @param[in] id        L'id de l'interaction à enlever
 */
void FicheContact::RemoveInteraction(int id)
{
    std::vector<int> indexInteractionsASupprimer;

    for (int index = 0; index < static_cast<int>(listInteraction.size()); index++){
        if (listInteraction[index].getId() == id){
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

/**
 * @brief Retourne un string contenant le nom tout en majuscule et le prénom commençant par une majuscule
 * @return un string contenant le nom et le prénom
 */
std::string FicheContact::ToString()
{
    std::string nom = this->nom;
    std::string prenom = this->prenom;

    std::transform(nom.begin(), nom.end(), nom.begin(), ::toupper);  //::toupper car std::toupper n'est pas accepté
    prenom[0] = std::toupper(prenom[0]);

    return nom + ' ' + prenom;
}
