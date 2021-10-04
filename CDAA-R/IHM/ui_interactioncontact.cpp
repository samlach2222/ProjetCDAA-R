/**
 * @file IHM/ui_interactioncontact.cpp
 * @brief Permet de gèrer l'ajout ou la suppression d'une interaction d'un contact
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 23/09/2021
 */

#include "ui_interactioncontact.h"
#include "ui_ui_interactioncontact.h"

#include <LOGIC/gestioncontact.h>

#include <QMessageBox>

bool ModeAjoutInteraction = 1;

/**
 * @brief Constructeur de UI_InteractionContact
 * @param[ou] parent    QWidget de création de classe
 */
UI_InteractionContact::UI_InteractionContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_InteractionContact)
{
    ui->setupUi(this);
    ui->frameEditInteraction->setVisible(0);
}
/**
 * @brief Destructeur de UI_InteractionContact
 */
UI_InteractionContact::~UI_InteractionContact()
{
    delete ui;
}

/**
 * @brief Methode liée au bouton permettant de valider la liste des intégrations
 * @todo A PROGRAMMER
 */
void UI_InteractionContact::ValidateAllInteractions()
{
    //TODO
}

/**
 * @brief Methode liée au bouton permettant d'annuler l'ajout et de fermer la fenêtre
 * @todo A PROGRAMMER
 */
void UI_InteractionContact::CancelAllInteractions()
{
    this->~UI_InteractionContact();
}

/**
 * @brief Methode liée au bouton permettant d'ajouter une interaction à un contact
 */
void UI_InteractionContact::AddInteraction()
{
    ModeAjoutInteraction = 1;
    ui->frameEditInteraction->setVisible(1);
    ui->editDateCreation->setDisabled(1);

    ui->editTitre->clear();
    ui->editDescription->clear();
}

/**
 * @brief Methode liée au bouton permettant de supprimer l'ajout une interaction d'un contact
 * @todo A PROGRAMMER
 */
void UI_InteractionContact::SupprimerInteraction()
{
    //TODO
}

/**
 * @brief Methode liée au bouton permettant de valider l'ajout d'une interaction
 */
void UI_InteractionContact::ValiderInteraction()
{
    /*if(ui->editTitre->text().isEmpty() && !(ui->editDescription->text().isEmpty()))    // si Champ NOM vide
    {
        ui->editTitre->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editDescription->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"nom\" est obligatoire.") );
    }
    else if(ui->editDescription->text().isEmpty() && !(ui->editTitre->text().isEmpty()))   // si Champ PRENOM vide
    {
        ui->editDescription->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
        ui->editTitre->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"prénom\" est obligatoire.") );
    }
    else if(ui->editTitre->text().isEmpty() && ui->editDescription->text().isEmpty())  // si les champs NOM et PRENOM sont vides
    {
        ui->editTitre->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editDescription->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Les champs \"nom\" et \"prénom\" sont obligatoires.") );
    }
    else
    {
        if(!ModeAjout)
        {
            QList<QListWidgetItem*> selectedItem = ui->ContactList->selectedItems();
            QVariant v = selectedItem[0]->data(Qt::UserRole);
            int idContact = v.value<int>();

            FicheContact contact = gc.GetContact(idContact);
            contact.setNom(ui->editNom->text().toStdString());
            contact.setPrenom(ui->editPrenom->text().toStdString());
            contact.setEntreprise(ui->editEntreprise->text().toStdString());
            contact.setMail(ui->editMail->text().toStdString());
            contact.setTelephone(ui->editTelephone->text().toStdString());
            contact.setPhoto(ui->Image->pixmap()->toImage());
            gc.ModifyContact(contact);
        }
        else
        {
            std::string nom = ui->editNom->text().toStdString();
            std::string prenom = ui->editPrenom->text().toStdString();
            std::string entreprise = ui->editEntreprise->text().toStdString();
            std::string mail = ui->editMail->text().toStdString();
            std::string telephone = ui->editTelephone->text().toStdString();
            QImage image = ui->Image->pixmap()->toImage();
            gc.AddContact(nom,prenom,entreprise,mail,telephone,image);
        }
        ui->frameEditContact->setVisible(0);
        this->DisplayContactList();
        this->RefreshLog();
        ui->editNom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        ui->editPrenom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
    }*/
}

void UI_InteractionContact::ReceiveIdToInteraction(int idreceive, GestionContact gc)
{
    this->listInteractions = gc.GetContact(idreceive).GetListInteraction();
    this->DisplayContactList();
}

void UI_InteractionContact::DisplayContactList()
{
    ui->InteractionList->clear();
    for(Interaction i : this->listInteractions)
    {
        QString str = QString::fromStdString(i.getTitre());
        QListWidgetItem* item = new QListWidgetItem(str);
        ui->InteractionList->addItem(item);
    }
}

void UI_InteractionContact::ListItemClick()
{

    /*ModeAjout = 0;
    QList<QListWidgetItem*> selectedItem = ui->ContactList->selectedItems();
    QVariant v = selectedItem[0]->data(Qt::UserRole);
    int idContact = v.value<int>();

    FicheContact contact = gc.GetContact(idContact);

    ui->frameEditContact->setVisible(1);

    ui->editNom->setText(QString::fromStdString(contact.getNom()));
    ui->editPrenom->setText(QString::fromStdString(contact.getPrenom()));
    ui->editEntreprise->setText(QString::fromStdString(contact.getEntreprise()));
    ui->editMail->setText(QString::fromStdString(contact.getMail()));
    ui->editTelephone->setText(QString::fromStdString(contact.getTelephone()));

    ui->editDateCreation->setText(QString::fromStdString(contact.getDateCreation().ToString()));
    ui->editDateCreation->setEnabled(0);

    QPixmap image = QPixmap::fromImage(contact.getPhoto());
    int w = ui->Image->width();
    int h = ui->Image->height();
    ui->Image->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));*/
}
