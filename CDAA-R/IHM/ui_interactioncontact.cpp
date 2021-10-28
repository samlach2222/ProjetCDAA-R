/**
 * @file IHM/ui_interactioncontact.cpp
 * @brief Permet de gèrer l'ajout ou la suppression d'une interaction d'un contact
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 23/09/2021
 */

#include "ui_interactioncontact.h"
#include "ui_ui_interactioncontact.h"

#include "../LOGIC/horodatage.h"
#include "../LOGIC/soundplayer.h"
#include "../LOGIC/tagsinteraction.h"

#include <QDate>
#include <QMessageBox>

/**
 * @brief Variable Booléenne pour savoir si on modifie ou si on crée une intéraction
 */
bool ModeAjoutInteraction = 1;

/**
 * @brief Constructeur de UI_InteractionContact
 * @param[out] parent    QWidget de création de classe
 * @todo Gèrer les tags comme dans la consigne
 */
UI_InteractionContact::UI_InteractionContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_InteractionContact),
    contact(NULL, "","","","","",QImage(), Horodatage())
{
    ui->setupUi(this);

    QPixmap QPAddContact(":/Ressources/Icons/AddInteractionContact rogne.png");
    int wai = ui->BAddInteraction->width() * 80/100;  //100% dépasse les bords, 90% touche les bords
    int hai = ui->BAddInteraction->height() * 80/100;
    ui->BAddInteraction->setIcon(QPAddContact);
    ui->BAddInteraction->setIconSize(QSize(wai,hai));

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
 * @brief Override de la méthode appelée lors d'une demande de fermeture de la fenêtre
 * @param[out] event     Event de fermeture de la fenêtre
 */
void UI_InteractionContact::closeEvent(QCloseEvent *event)
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    emit sendContactToMainWindow(this->contact);

    //event->ignore();  //Empêche la fermeture de la fenêtre
    //event->accept();  //Ré-autorise la fermeture de la fenêtre si ignore() appelé
}

/**
 * @brief Methode liée au bouton permettant d'ajouter une interaction à un contact
 */
void UI_InteractionContact::AddInteraction()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    ModeAjoutInteraction = 1;
    ui->frameEditInteraction->setVisible(1);

    ui->editTitre->clear();
    ui->editDescription->clear();
}

/**
 * @brief Methode liée au bouton permettant de supprimer l'ajout une interaction d'un contact
 */
void UI_InteractionContact::SupprimerInteraction()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    if(this->contact.getListInteraction().size() > 0 && !ModeAjoutInteraction)
    {
        QList<QListWidgetItem*> selectedItem = ui->InteractionList->selectedItems();
        QVariant v = selectedItem[0]->data(Qt::UserRole);
        int idInteraction = v.value<int>();

        this->contact.RemoveInteraction(idInteraction);
        this->DisplayInteractionList();
        ui->frameEditInteraction->setVisible(0);
        emit AddOperationToLog("Interaction Deleted");
    }
}

/**
 * @brief Methode liée au bouton permettant de valider l'ajout d'une interaction
 */
void UI_InteractionContact::ValiderInteraction()
{
    if(ui->editTitre->text().isEmpty() && !(ui->editDescription->toPlainText().isEmpty()))    // si Champ NOM vide
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editTitre->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editDescription->setStyleSheet("QPlainTextEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"titre\" est obligatoire.") );
    }
    else if(ui->editDescription->toPlainText().isEmpty() && !(ui->editTitre->text().isEmpty()))   // si Champ PRENOM vide
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editDescription->setStyleSheet("QPlainTextEdit { border-style: outset; border-width: 2px; border-color: red;}");
        ui->editTitre->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"description\" est obligatoire.") );
    }
    else if(ui->editTitre->text().isEmpty() && ui->editDescription->toPlainText().isEmpty())  // si les champs NOM et PRENOM sont vides
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editTitre->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editDescription->setStyleSheet("QPlainTextEdit { border-style: outset; border-width: 2px; border-color: red;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Les champs \"titre\" et \"description\" sont obligatoires.") );
    }
    else
    {
        // On joue le son du bouton
        SoundPlayer::PlayButtonSound();

        if(!ModeAjoutInteraction)
        {
            QList<QListWidgetItem*> selectedItem = ui->InteractionList->selectedItems();
            QVariant v = selectedItem[0]->data(Qt::UserRole);
            int idInteraction = v.value<int>();

            for(Interaction &i : this->contact.getListInteraction())
            {
                if(i.getId() == idInteraction)
                {
                    i.setTitre(ui->editTitre->text().toStdString());
                    i.setContenu(ui->editDescription->toPlainText().toStdString());
                }
            }
            emit AddOperationToLog("Interaction Modified");
        }
        else
        {

            std::string titre = ui->editTitre->text().toStdString();
            std::string contenu = ui->editDescription->toPlainText().toStdString();

            contact.AddInteraction(contenu, titre);

            //Interaction* i = this->contact.GetListInteraction().data();
            //Interaction inte = i[this->contact.GetListInteraction().size()-1];
            //Interaction* ptr = &inte;

            //Interaction* ptr = &this->contact.GetListInteraction().data()[this->contact.GetListInteraction().size()-1];
            emit AddOperationToLog("Interaction Added");
        }
        ui->frameEditInteraction->setVisible(0);
        this->DisplayInteractionList();
        ui->editDescription->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        ui->editTitre->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
    }
}

/**
 * @brief Slot permettant de récupérer la gestion contact et l'id du contact courant pour les interactions
 * @param[in] idreceive id du contact courant
 * @param[in] gc    Gestion contact
 */
void UI_InteractionContact::ReceiveIdToInteraction(int idreceive,GestionContact gc)
{
    this->contact = gc.GetContact(idreceive);
    this->DisplayInteractionList();
}

/**
 * @brief Méthode permettant d'afficher la liste des interactions dans l'IHM
 */
void UI_InteractionContact::DisplayInteractionList()
{
    ui->InteractionList->clear();
    for(Interaction i : this->contact.getListInteraction())
    {
        QString str = QString::fromStdString(i.getTitre());
        QListWidgetItem* item = new QListWidgetItem(str);
        QVariant v;
        v.setValue(i.getId());
        item->setData(Qt::UserRole, v);
        ui->InteractionList->addItem(item);
    }
}

/**
 * @brief Méthode reliée à l'action d'un click sur un élément de la liste, permet d'afficher la fenêtre d'édition d'une interaction
 */
void UI_InteractionContact::ListItemClick()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    ModeAjoutInteraction = 0;
    QList<QListWidgetItem*> selectedItem = ui->InteractionList->selectedItems();
    QVariant v = selectedItem[0]->data(Qt::UserRole);
    int idInteraction = v.value<int>();


    ui->frameEditInteraction->setVisible(1);

    for(Interaction i : this->contact.getListInteraction())
    {
        if(i.getId() == idInteraction)
        {
            ui->editTitre->setText(QString::fromStdString(i.getTitre()));
            ui->editDescription->setPlainText(QString::fromStdString(i.getContenu()));
            ui->editDateCreation->setText(QString::fromStdString(i.getHorodatage().ToString()));
        }
    }
}
