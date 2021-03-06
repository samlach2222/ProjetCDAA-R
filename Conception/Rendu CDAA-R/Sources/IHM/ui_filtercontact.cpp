/**
 * @file IHM/ui_filtercontact.cpp
 * @brief Permet d'appliquer des filtres sur une recherche de contacts
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 23/09/2021
 */

#include "ui_filtercontact.h"
#include "ui_ui_filtercontact.h"

#include <LOGIC/soundplayer.h>

#include <QMessageBox>

/**
 * @brief Constructeur de UI_FilterContact
 *
 * Constructeur de la classe IHM de filtrage de contacts. Celui-ci initialise l'affichage graphique de la fenêtre de filtrage.
 * @param[out] parent   QWidget de création de classe
 * @author Samuel LACHAUD
 */
UI_FilterContact::UI_FilterContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_FilterContact)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de UI_FilterContact
 *
 * Destructeur de la classe de filtrage de contacts. Il permet de supprimer l'affichage graphique de la fenêtre de filtrage.
 * @author Samuel LACHAUD
 */
UI_FilterContact::~UI_FilterContact()
{
    delete ui;
}

/**
 * @brief Permet de valider le filtre à partir du bouton lié
 *
 * Méthode liée a l'appuis sur le bouton valider du filtrage.
 * Il permet d'appliquer le filtre saisi sur la liste de contact de la MainWindow1
 * @author Loïs PAZOLA
 */
void UI_FilterContact::ButtonValidate()
{
    if(this->VerificationChamps()) // si les champs sont valides et bien remplis
    {
        PrepareSendingToMainWindow(this->gc);
    }
}

/**
 * @brief Override de la méthode appelée lors d'une demande de fermeture de la fenêtre
 *
 * Redéfinition de la méthode de fermeture de la fenêtre afin d'appliquer le son du bouton.
 * @param[out] event     Event de fermeture de la fenêtre
 * @author Loïs PAZOLA
 */
void UI_FilterContact::closeEvent(QCloseEvent *event)
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    //event->ignore();  //Empêche la fermeture de la fenêtre
    //event->accept();  //Ré-autorise la fermeture de la fenêtre si ignore() appelé
}

/**
 * @brief Méthode permettant de vérifier que les champs sont remplis correctement
 *
 * Méthode appelée lors de la validation du filtrage pour vérifier si les champs obligatoire pour la bonne exécution du filtrage sont remplis correctement.
 * Le cas contraire, une erreur est affichée à l'utilisateur, et celui-ci est invité à remplir correctement les champs necéssaires.
 * @author Samuel LACHAUD
 * @return Retourne true si les champss sont bien remplis et false s'il ne le sont pas
 */
bool UI_FilterContact::VerificationChamps()
{
    bool champsCorrects = true;

    // DEBUT check champs nom et entreprise

    if(!ui->editNom->text().isEmpty() && !ui->editEntreprise->text().isEmpty())    // si les deux champs nom et entreprise sont pas vides
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editNom->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editEntreprise->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Veuillez remplir uniquement l'un des deux champs suivants : \"nom\" ou \"entreprise\".") );
        champsCorrects = false;
    }
    else if(ui->editNom->text().isEmpty() && ui->editEntreprise->text().isEmpty()) // si les deux champs nom et entreprise sont vides
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editNom->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editEntreprise->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Veuillez remplir l'un des deux champs suivants : \"nom\" ou \"entreprise\".") );
        champsCorrects = false;
    }
    else // si les champs sont corrects
    {
        ui->editNom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        ui->editEntreprise->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
    }

    // FIN check champs nom et entreprise

    // DEBUT check champs dateDebut et dateFin

    if(ui->editDateDebut->text().isEmpty() && ui->editDateFin->text().isEmpty()) // si les deux champs dateDebut et dateFin sont vides
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editDateDebut->setStyleSheet("QDateEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editDateFin->setStyleSheet("QDateEdit {border-style: outset; border-width: 2px; border-color: red;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Veuillez remplir les deux champs de dates.") );
        champsCorrects = false;
    }
    else if(!ui->editDateDebut->text().isEmpty() && ui->editDateFin->text().isEmpty()) // si seul le champ dateDebut est remplis
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editDateDebut->setStyleSheet("QDateEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        ui->editDateFin->setStyleSheet("QDateEdit {border-style: outset; border-width: 2px; border-color: red;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Veuillez remplir le champ \"Date de fin\".") );
        champsCorrects = false;
    }
    else if(ui->editDateDebut->text().isEmpty() && !ui->editDateFin->text().isEmpty()) // si seul le champ dateFin est remplis
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editDateDebut->setStyleSheet("QDateEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editDateFin->setStyleSheet("QDateEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Veuillez remplir le champ \"Date de début\".") );
        champsCorrects = false;
    }
    else // si les champs sont corrects
    {
        ui->editDateDebut->setStyleSheet("QDateEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        ui->editDateFin->setStyleSheet("QDateEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
    }

    // Pas besoin de vérifier les radio bouton puisque forcément un seul des deux est coché.

    return champsCorrects;
}

/**
 * @brief Permet de recevoir la classe de gestion de contact afin d'avoir la liste complête des contacts
 *
 * Slot permettant de recevoir la classe de gestion de contact pour pouvoir appliquer les filtres sur la liste de contacts.
 * La classe de gestion de contact nous sert donc a récupérer la liste de contacts.
 * @author Samuel LACHAUD
 * @param[in] gc classe de Gestion de contacts
 */
void UI_FilterContact::ReceiveFromMainWindow(GestionContact gc)
{
    this->gc = gc;
    QDate minDate;
    QDate maxDate;
    for(const FicheContact &fc : gc.GetAllContacts())
    {
        if(minDate.toString().isEmpty() && maxDate.toString().isEmpty()){
            minDate = QDate(fc.getDateCreation().getAnnee(), fc.getDateCreation().getMois(), fc.getDateCreation().getJour());
            maxDate = QDate(fc.getDateCreation().getAnnee(), fc.getDateCreation().getMois(), fc.getDateCreation().getJour());
        }
        else
        {
            QDate curDate = QDate(fc.getDateCreation().getAnnee(), fc.getDateCreation().getMois(), fc.getDateCreation().getJour());
            if(curDate < minDate)
            {
                minDate = curDate;
            }
            else if(curDate > maxDate)
            {
                maxDate = curDate;
            }
        }
    }
    ui->editDateDebut->setDate(minDate);
    ui->editDateFin->setDate(maxDate);
}

/**
 * @brief Crée la liste des contacts filtrés et l'envoie au MainWindow
 *
 * Méthode permettant de mettre en place le filtrage des contacts.
 * Pour celà la liste de contact va être modifiée, filtrée, puis envoyée au MainWindow.
 * @author Loïs PAZOLA
 * @param gc    GestionContact utilisé pour le filtrage
 */
void UI_FilterContact::PrepareSendingToMainWindow(GestionContact gc)
{
    this->gc = gc;

    std::vector<FicheContact> listContact = std::vector<FicheContact>();
    QDate dateMin = QDate::fromString(ui->editDateDebut->text(),"dd/MM/yyyy");
    QDate dateMax = QDate::fromString(ui->editDateFin->text(),"dd/MM/yyyy");

    for(const FicheContact &fc : this->gc.GetAllContacts())
    {
        //Check de la validité de la date
        int fcAnnee = fc.getDateCreation().getAnnee();
        int fcMois = fc.getDateCreation().getMois();
        int fcJour = fc.getDateCreation().getJour();
        QDate date = QDate(fcAnnee,fcMois, fcJour);
        if(date >= dateMin && date <= dateMax) // date souhaitée
        {
            // check nom (si non vide)
            if(!ui->editNom->text().isEmpty())
            {
                if(fc.getNom() == ui->editNom->text().toStdString()) // si le nom est bien recherché
                {
                    listContact.push_back(fc);
                }
            }
            //check entreprise (si non vide)
            else if(!ui->editEntreprise->text().isEmpty())
            {
                if(fc.getEntreprise() == ui->editEntreprise->text().toStdString()) // si l'entreprise est bien recherché
                {
                    listContact.push_back(fc);
                }
            }
        }
    }

    if(ui->triAlphabetique->isChecked())    // tri alphabétique
    {
        if(!ui->editNom->text().isEmpty()) // on trie alors par Prénom
        {
            std::sort(listContact.begin(), listContact.end(), [](FicheContact& fiche1, FicheContact& fiche2) {
                return fiche1.getPrenom() < fiche2.getPrenom();
            });
        }
        else if(!ui->editEntreprise->text().isEmpty()) // on trie alors par Nom
        {
            std::sort(listContact.begin(), listContact.end(), [](FicheContact& fiche1, FicheContact& fiche2) {
                return fiche1.getNom() < fiche2.getNom();
            });
        }
    }
    else if(ui->triDateCreation->isChecked())   // tri par date de création
    {

        std::sort(listContact.begin(), listContact.end(), [](FicheContact& fiche1, FicheContact& fiche2) {
            // fiche1
            std::string fcAnnee1 = std::to_string(fiche1.getDateCreation().getAnnee());
            std::string fcMois1 = std::to_string(fiche1.getDateCreation().getMois());
            std::string fcJour1 = std::to_string(fiche1.getDateCreation().getJour());
            QDate date1 = QDate::fromString(QString::fromStdString(fcJour1 + "/" + fcMois1 + "/" + fcAnnee1),"dd/MM/yyyy");
            // fiche2
            std::string fcAnnee2 = std::to_string(fiche2.getDateCreation().getAnnee());
            std::string fcMois2 = std::to_string(fiche2.getDateCreation().getMois());
            std::string fcJour2 = std::to_string(fiche2.getDateCreation().getJour());
            QDate date2 = QDate::fromString(QString::fromStdString(fcJour2 + "/" + fcMois2 + "/" + fcAnnee2),"dd/MM/yyyy");
            return date1 < date2;
        });
    }
    emit sendListContactToMainWindow(listContact);
    this->close();
}
