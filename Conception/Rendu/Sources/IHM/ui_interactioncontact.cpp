/**
 * @file IHM/ui_interactioncontact.cpp
 * @brief Permet de gèrer l'ajout ou la suppression d'une interaction d'un contact
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 23/09/2021
 */

#include "ui_interactioncontact.h"
#include "ui_ui_interactioncontact.h"

#include <LOGIC/horodatage.h>
#include <LOGIC/soundplayer.h>
#include <LOGIC/tagsinteraction.h>

#include <QDate>
#include <QMessageBox>

#include <STORAGE/databasestorage.h>

/**
 * @brief Valeur booléenne pour savoir si on ajoute une interaction ou si on l'édite
 *
 * Ce boolean permettra de savoir une fois que l'on effectue l'appuis sur le bouton de validation de l'interaction si on est en train de modifier ou d'ajouter le contact.
 * Les finalités seront donc différentes, de même pour l'affichage dans les logs.
 */
bool ModeAjoutInteraction = 1;

/**
 * @brief Constructeur de UI_InteractionContact
 *
 * Constructeur de la fenêtre de gestion des intéractions.
 * Dans ce constructeur, des valeurs sont initialisées comme un contact temporaire et une image de bouton
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @param[out] parent    QWidget de création de classe
 */
UI_InteractionContact::UI_InteractionContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_InteractionContact),
    contact(-1, "","","","","",QImage(), Horodatage())
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
 *
 * Destructeur de la fenêtre de gestion des intéractions d'un contact.
 * Ce destructeur détruit la fenêtre avec les composants graphiques qui lui sont liés.
 * @author Samuel LACHAUD
 */
UI_InteractionContact::~UI_InteractionContact()
{
    delete ui;
}

/**
 * @brief Override de la méthode appelée lors d'une demande de fermeture de la fenêtre
 *
 * Redéfinition de la méthode de fermeture de la fenêtre afin d'appliquer le son du bouton et de revenir à l'état initial de la fenêtre.
 * C'est également à ce moment que le contact est renvoyé à la MainWindow.
 * @param[out] event     Event de fermeture de la fenêtre
 * @author Loïs PAZOLA
 */
void UI_InteractionContact::closeEvent(QCloseEvent *event)
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    emit sendContactToMainWindow(this->contact);

    ui->editTitre->clear();
    ui->editDescription->clear();
    ui->frameEditInteraction->setVisible(0);

    //event->ignore();  //Empêche la fermeture de la fenêtre
    //event->accept();  //Ré-autorise la fermeture de la fenêtre si ignore() appelé
}

/**
 * @brief Methode liée au bouton permettant d'ajouter une interaction à un contact
 *
 * Méthode actionnée par le bouton d'ajout d'interaction sur la fenêtre, il permet d'afficher le panel d'ajout d'interaction sur l'écran.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
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
 *
 * Méthode actionnée par le bouton de suppression d'interaction sur la fenêtre.
 * L'intéraction sélectionnée dans la liste est donc supprimée de celle-ci.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
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
 * @brief Permet de sauvegarder une nouvelle interaction ou la modification d'une interaction déjà existante avec le bouton valider
 *
 * Méthode effectuée suite à l'appuis sur le bouton de validation, en fonction de la variable globale ModeAjoutInteraction, la méthode va donc enregistrer la nouvelle intéraction ou modifier l'ancienne.
 * Les champs obligatoires doivent être remplis, ou l'exécution de cette méthode provoquera une erreur à l'utilisateur.
 * @author Samuel LACHAUD
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
                    DatabaseStorage::UpdateInteractionAndTags(i);
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
 *
 * Slot qui permet de récupérer l'id du contact auquel on rajoute/supprime/modifie une ou plusieurs interactions.
 * Elle récupère également la gestionContact afin de sauvegarder.
 * La liste d'intéraction est alors affichée à ce moment sur la fenêtre d'interactions.
 * @author Samuel LACHAUD
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
 *
 * Méthode permettant d'afficher les interactions sur la liste prévue à cet effet sur la fenêtre.
 * A partir du contact on liste toutes les intéraction de celui-ci.
 * @author Samuel LACHAUD
 */
void UI_InteractionContact::DisplayInteractionList()
{
    ui->InteractionList->clear();
    for(const Interaction &i : this->contact.getListInteraction())
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
 * @brief Méthode reliée à la sélection d'un élément de la liste, permet d'afficher la fenêtre d'édition d'une interaction
 *
 * Méthode permettant quand on clique sur une intéraction dans la liste sur la fenêtre d'afficher le panel de modification/création de celui-ci.
 * Les éléments permettant alors cette édition sont affichés ainsi que les boutons d'acceptation ou d'annulation.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
void UI_InteractionContact::ListItemSelected()
{
    // La fonction est aussi appelé quand la liste est vidée (avec la fonction clear)
    // Si nous sommes dans ce cas là, ne rien faire
    QList<QListWidgetItem*> selectedItems = ui->InteractionList->selectedItems();
    if (!selectedItems.isEmpty())
    {
        // On joue le son du bouton
        SoundPlayer::PlayButtonSound();

        ModeAjoutInteraction = 0;
        QVariant v = selectedItems[0]->data(Qt::UserRole);
        int idInteraction = v.value<int>();

        ui->frameEditInteraction->setVisible(1);

        for(const Interaction &i : this->contact.getListInteraction())
        {
            if(i.getId() == idInteraction)
            {
                ui->editTitre->setText(QString::fromStdString(i.getTitre()));
                ui->editDescription->setPlainText(QString::fromStdString(i.getContenu()));
                ui->editDateCreation->setText(QString::fromStdString(i.getDateCreation().ToString()));
            }
        }
    }
}
