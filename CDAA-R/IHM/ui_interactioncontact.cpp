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
    ui(new Ui::UI_InteractionContact),
    contact(NULL, "","","","","",QImage(), Horodatage())
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
    if(this->contact.GetListInteraction().size() > 0)
    {
        QList<QListWidgetItem*> selectedItem = ui->InteractionList->selectedItems();
        QVariant v = selectedItem[0]->data(Qt::UserRole);
        int idInteraction = v.value<int>();

        this->contact.RemoveInteraction(idInteraction);
        this->DisplayInteractionList();
        ui->frameEditInteraction->setVisible(0);
    }
}

/**
 * @brief Methode liée au bouton permettant de valider l'ajout d'une interaction
 * @todo changer pour le constr et l'ajout par fiche contact
 */
void UI_InteractionContact::ValiderInteraction()
{
    if(ui->editTitre->text().isEmpty() && !(ui->editDescription->toPlainText().isEmpty()))    // si Champ NOM vide
    {
        ui->editTitre->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editDescription->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"nom\" est obligatoire.") );
    }
    else if(ui->editDescription->toPlainText().isEmpty() && !(ui->editTitre->text().isEmpty()))   // si Champ PRENOM vide
    {
        ui->editDescription->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
        ui->editTitre->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"prénom\" est obligatoire.") );
    }
    else if(ui->editTitre->text().isEmpty() && ui->editDescription->toPlainText().isEmpty())  // si les champs NOM et PRENOM sont vides
    {
        ui->editTitre->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editDescription->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Les champs \"nom\" et \"prénom\" sont obligatoires.") );
    }
    else
    {
        if(!ModeAjoutInteraction)
        {
            QList<QListWidgetItem*> selectedItem = ui->InteractionList->selectedItems();
            QVariant v = selectedItem[0]->data(Qt::UserRole);
            int idInteraction = v.value<int>();

            for(Interaction i : this->contact.GetListInteraction())
            {
                if(i.GetId() == idInteraction)
                {
                    i.setTitre(ui->editTitre->text().toStdString());
                    i.SetContenu(ui->editDescription->toPlainText().toStdString());
                }
            }
        }
        else
        {

            std::string titre = ui->editTitre->text().toStdString();
            std::string contenu = ui->editDescription->toPlainText().toStdString();

            contact.AddInteraction(contenu, titre);

        }
        ui->frameEditInteraction->setVisible(0);
        this->DisplayInteractionList();
        ui->editDescription->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        ui->editTitre->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
    }
}

void UI_InteractionContact::ReceiveIdToInteraction(int idreceive,GestionContact gc)
{
    this->contact = gc.GetContact(idreceive);
    this->DisplayInteractionList();
}

void UI_InteractionContact::DisplayInteractionList()
{
    ui->InteractionList->clear();
    for(Interaction i : this->contact.GetListInteraction())
    {
        QString str = QString::fromStdString(i.getTitre());
        QListWidgetItem* item = new QListWidgetItem(str);
        QVariant v;
        v.setValue(i.GetId());
        item->setData(Qt::UserRole, v);
        ui->InteractionList->addItem(item);
    }
}

void UI_InteractionContact::ListItemClick()
{

    ModeAjoutInteraction = 0;
    QList<QListWidgetItem*> selectedItem = ui->InteractionList->selectedItems();
    QVariant v = selectedItem[0]->data(Qt::UserRole);
    int idInteraction = v.value<int>();


    ui->frameEditInteraction->setVisible(1);

    for(Interaction i : this->contact.GetListInteraction())
    {
        if(i.GetId() == idInteraction)
        {
            ui->editTitre->setText(QString::fromStdString(i.getTitre()));
            ui->editDescription->setPlainText(QString::fromStdString(i.GetContenu()));
            ui->editDateCreation->setText(QString::fromStdString(i.GetHorodatage().ToString()));
            ui->editDateCreation->setEnabled(0);
        }
    }
}
