/**
 * @file IHM/mainwindow.cpp
 * @brief Fenêtre principale de l'application permettant d'afficher les contacts, leur édition et toutes les autres actions souhaitées
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.1
 * @date 10/12/2021
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <LOGIC/soundplayer.h>
#include <STORAGE/databasestorage.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QStringListModel>

/**
 * @brief Valeur booléenne pour savoir si on ajoute un contact ou si on l'édite
 *
 * Ce boolean permettra de savoir une fois que l'on effectue l'appuis sur le bouton de validation de contact si on est en train de modifier ou d'ajouter le contact.
 * Les finalités seront donc différentes, de même pour l'affichage dans les logs.
 */
bool ModeAjout = 0;


/**
 * @brief Constructeur de mainwindows
 *
 * Constructeur du MainWindow, cette méthode est appelée par le main à l'ouverture de l'application afin d'obtenir la fenêtre principale.
 * @param[out] parent    QWidget de création de classe
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initialisation des sous-fenêtres
    fc = new UI_FilterContact;
    rc = new UI_RequestContact;
    sgc = new UI_SaveGestionContact;
    ic = new UI_InteractionContact;

    //DEBUT DEFINITION SIGNAUX
    QObject::connect(this, SIGNAL(sendIdToInteraction(int,GestionContact)), ic, SLOT(ReceiveIdToInteraction(int,GestionContact)));
    QObject::connect(ic, SIGNAL(sendContactToMainWindow(FicheContact)), this, SLOT(ReceiveContactToMainWindow(FicheContact)));
    QObject::connect(ic, SIGNAL(AddOperationToLog(std::string)), this, SLOT(AddOperationToLog(std::string)));
    QObject::connect(this, SIGNAL(sendToFilterContact(GestionContact)), fc, SLOT(ReceiveFromMainWindow(GestionContact)));
    QObject::connect(fc, SIGNAL(sendListContactToMainWindow(std::vector<FicheContact>)), this, SLOT(ReceiveFromFilterContact(std::vector<FicheContact>)));
    QObject::connect(this, SIGNAL(sendGcToSaveGestionContact(GestionContact)), sgc, SLOT(getGcFromMainWindow(GestionContact)));
    QObject::connect(sgc, SIGNAL(sendGcToMainWindow(GestionContact)), this, SLOT(getGcFromSaveGestionContact(GestionContact)));
    QObject::connect(this, SIGNAL(sendGcToRequestContact(GestionContact)), rc, SLOT(getGcFromMainWindow(GestionContact)));
    QObject::connect(this, SIGNAL(refreshFilteredContacts(GestionContact)), fc, SLOT(PrepareSendingToMainWindow(GestionContact)));
    //FIN DEFINITION SIGNAUX

    //Création du dossier qui contiendra la base de données et le JSON
    QDir appDataDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!appDataDir.exists()){
        appDataDir.mkpath(".");
    }

    //Initialisation et chargement de la BDD
    DatabaseStorage::InitializeBDD();
    gc = DatabaseStorage::Load();

    idContactSelectionne = -1;
    DisplayContactList();
    this->RefreshLog();

    // Edition des controlleurs par défaut
    ui->frameEditContact->setVisible(0);
    ui->ChooseImage->setStyleSheet("QPushButton { background-color: rgba(10, 0, 0, 0); }");

    // Gestion de la taille relative des icones des boutons avec 90% du bouton
    QPixmap QPFilterContact(":/Ressources/Icons/FilterContact.png");
    int wfc = ui->BFilterContact->width() * 90/100;
    int hfc = ui->BFilterContact->height() * 90/100;
    ui->BFilterContact->setIcon(QPFilterContact);
    ui->BFilterContact->setIconSize(QSize(wfc,hfc));

    QPixmap QPSaveGestionContact(":/Ressources/Icons/SaveGestionContact.png");
    int wsgc = ui->BSaveGestionContact->width() * 90/100;
    int hsgc = ui->BSaveGestionContact->height() * 90/100;
    ui->BSaveGestionContact->setIcon(QPSaveGestionContact);
    ui->BSaveGestionContact->setIconSize(QSize(wsgc,hsgc));

    QPixmap QPRequestContact(":/Ressources/Icons/RequestContact.png");
    int wrc = ui->BRequestContact->width() * 90/100;
    int hrc = ui->BRequestContact->height() * 90/100;
    ui->BRequestContact->setIcon(QPRequestContact);
    ui->BRequestContact->setIconSize(QSize(wrc,hrc));

    QPixmap QPAddContact(":/Ressources/Icons/AddContact rogne.png");
    int wac = ui->BAddContact->width() * 80/100;  //100% dépasse les bords, 90% touche les bords
    int hac = ui->BAddContact->height() * 80/100;
    ui->BAddContact->setIcon(QPAddContact);
    ui->BAddContact->setIconSize(QSize(wac,hac));
}
/**
 * @brief Destructeur de MainWindow
 *
 * Destructeur de MainWindow, il permet de supprimer les instances des autres classes d'UI, permettant donc de les fermer et de ne pas les laisser en mémoire.
 * @author Samuel LACHAUD
 */
MainWindow::~MainWindow()
{
    // On supprime toutes les sous-fenêtres
    delete fc;
    delete rc;
    delete sgc;
    delete ic;

    delete ui;
}

/**
 * @brief Méthode associée au bouton d'ajout de contact permettant d'ajouter un contact à la gestion de contact
 *
 * Méthode assoiée au bouton d'ajout de contact, elle permet d'ajouter un contact à partir de tout les controlleurs (editText, etc.) à la classe GestionContact.
 * @author Samuel LACHAUD
 */
void MainWindow::AddContact()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    ModeAjout = 1;
    QPixmap image = QPixmap::fromImage(QImage(":/Ressources/Icons/unknownContact.png"));
    QIcon buttonIcon(image);
    ui->ChooseImage->setIcon(buttonIcon);
    ui->ChooseImage->setIconSize(ui->ChooseImage->size());

    ui->editNom->clear();
    ui->editPrenom->clear();
    ui->editEntreprise->clear();
    ui->editMail->clear();
    ui->editTelephone->clear();

    ui->frameEditContact->setVisible(1);

    this->RefreshLog();
}

/**
 * @brief Méthode pour rafraichir l'affichage de la liste des contacts en prenant en compte le filtrage
 *
 * Méthode permettant de raffraichir la liste affichée sur la MainWindow.
 * Elle prend en compte les changements des contacts, mais également l'application d'un filtrage, et le retrait de celui-ci.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
void MainWindow::DisplayContactList()
{
    ui->ContactList->clear();

    //Si le filtrage est activé, rafrachit la liste des contacts filtrés
    if (ui->BFilterContact->styleSheet().contains("QPushButton {background-color:red;")){
        emit refreshFilteredContacts(gc);
    }
    else{
        for(FicheContact c : gc.GetAllContacts())
        {
            QString str = QString::fromStdString(c.ToString());
            QListWidgetItem* item = new QListWidgetItem(str);
            QVariant v;
            v.setValue(c.getId());
            item->setData(Qt::UserRole, v);
            ui->ContactList->addItem(item);
        }
    }
}

/**
 * @brief Méthode permettant de rafraichir l'affichage des logs à chaque fois qu'une action est effectuée
 *
 * Méthode permettant de raffraichir la liste d'affichage de logs quand un contact ou une interaction est ajouté(e)/Supprimé(e)/Modifié(e)
 * @author Samuel LACHAUD
 */
void MainWindow::RefreshLog()
{
    QStringListModel* model = new QStringListModel(this);
    QStringList list;
    int tabSize = gc.getLog().getTabLog().size();
    for(int i =0; i < static_cast<int>(tabSize); i++)
    {
        QString text = QString::fromStdString(gc.getLog().getTabLog()[i]);
        list.append(text);
    }
    model->setStringList(list);
    ui->LogsList->setModel(model);

    //Réinitialise l'id sélectionné
    this->idContactSelectionne = -1;
}

/**
 * @brief Méthode permettant l'ouverture de FilterContact si aucune fenêtre n'est ouverte
 *
 * Méthode permettant l'ouverture de la fenêtre FilterContact si aucune autre fenêtre n'est ouverte.
 * Celle-ci permettra d'appliquer des filtres sur la liste de contacts présente sur la MainWindow.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
void MainWindow::OpenFC()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    if (ui->BFilterContact->styleSheet().contains("QPushButton {background-color:red;")){  //Ne pas vérifier le styleSheet avec == au cas où on veuille le modifier plus tard
        this->resetFilters();  //On désactive d'abord le filtrage si activé, il faut réappuyer pour ouvrir la fenêtre
    } else {
        if(!(rc->isVisible() || sgc->isVisible() || ic->isVisible())){
            emit sendToFilterContact(this->gc);
            fc->show();
        }
    }
}

/**
 * @brief Méthode permettant l'ouverture de RequestContact si aucune fenêtre n'est ouverte
 *
 * Méthode permettant l'ouverture de la fenêtre RequestContact si aucune fenêtre n'est ouverte.
 * Celle-ci permettra d'effectuer des requêtes prédéfinies sur la base de données de l'application.
 * @author Samuel LACHAUD
 */
void MainWindow::OpenRC()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    if(!(fc->isVisible() || sgc->isVisible() || ic->isVisible())){
        emit sendGcToRequestContact(this->gc);
        rc->show();
    }
}

/**
 * @brief Méthode permettant l'ouverte de SaveGestionContact si aucune fenêtre n'est ouverte
 *
 * Méthode permettant l'ouverture de la fenêtre SaveGestionContact si aucune fenêtre n'est ouverte.
 * Celle-ci permettra de sauvegarder ou d'importer différentes données de l'application depuis/dans un fichier JSON
 * @author Samuel LACHAUD
 */
void MainWindow::OpenSGC()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    if(!(fc->isVisible() || rc->isVisible() || ic->isVisible())){
        emit sendGcToSaveGestionContact(this->gc);
        sgc->show(); // pas StarGate Command
    }
}

/**
 * @brief Méthode liée au double clic sur un contact permettant l'ouverture de la fiche d'interaction, si aucune fenêtre n'est ouverte
 *
 * Méthode liée au double clic sur un contact permettant l'ouverture de la fiche d'interaction, si aucune fenêtre n'est ouverte.
 * L'ouverture de cette fenêtre permettra donc d'ajouter/modifier/supprimer des interactions du contact double-cliqué.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
void MainWindow::ListItemDoubleClick()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    QList<QListWidgetItem*> selectedItem = ui->ContactList->selectedItems();
    QVariant v = selectedItem[0]->data(Qt::UserRole);
    int idContact = v.value<int>();

    FicheContact contact = gc.GetContact(idContact);

    ic->setWindowTitle("Interactions de "+QString::fromStdString(contact.ToString()));
    emit sendIdToInteraction(idContact,this->gc);
    if(!(fc->isVisible() || rc->isVisible() || sgc->isVisible())){
        ic->show();
    }
}

/**
 * @brief Méthode liée à la sélection d'un contact permettant l'édition de celui-ci
 *
 * Méthode exécutée lors du clic sur un contact, la fiche contact s'affiche alors dans la zone à cet effet.
 * Le contact est alors modifiable ou supprimable. Ses donnes sont toutes éditables, sauf la date de création.
 * @author Samuel LACHAUD
 */
void MainWindow::ListItemSelected()
{
    // La fonction est aussi appelé quand la liste est vidée (avec la fonction clear)
    // Si nous sommes dans ce cas là, ne rien faire
    QList<QListWidgetItem*> selectedItems = ui->ContactList->selectedItems();
    if (!selectedItems.isEmpty())
    {
        QVariant v = selectedItems[0]->data(Qt::UserRole);
        if (idContactSelectionne != v.value<int>()){
            // On joue le son du bouton
            SoundPlayer::PlayButtonSound();

            ModeAjout = 0;
            idContactSelectionne = v.value<int>();

            FicheContact contact = gc.GetContact(idContactSelectionne);

            ui->editNom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
            ui->editPrenom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
            ui->editNom->setText(QString::fromStdString(contact.getNom()));
            ui->editPrenom->setText(QString::fromStdString(contact.getPrenom()));
            ui->editEntreprise->setText(QString::fromStdString(contact.getEntreprise()));
            ui->editMail->setText(QString::fromStdString(contact.getMail()));
            ui->editTelephone->setText(QString::fromStdString(contact.getTelephone()));

            ui->editDateCreation->setText(QString::fromStdString(contact.getDateCreation().ToString()));

            QPixmap image = QPixmap::fromImage(contact.getPhoto());
            QIcon buttonIcon(image);
            ui->ChooseImage->setIcon(buttonIcon);
            ui->ChooseImage->setIconSize(ui->ChooseImage->size());

            ui->frameEditContact->setVisible(1);
        }
    }
}

/**
 * @brief Permet de sauvegarder un nouveau contact ou la modification d'un contact déjà existant avec le bouton valider
 *
 * Méthode effectuée suite à l'appuis sur le bouton de validation, en fonction de la variable globale ModeAjout, la méthode va donc enregistrer le nouveau contact ou modifier l'ancien.
 * Les champs obligatoires doivent être remplis, ou l'exécution de cette méthode provoquera une erreur à l'utilisateur.
 * @author Samuel LACHAUD
 */
void MainWindow::ValiderContact()
{
    if(ui->editNom->text().isEmpty() && !(ui->editPrenom->text().isEmpty()))    // si Champ NOM vide
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editNom->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editPrenom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"Nom\" est obligatoire.") );

    }
    else if(ui->editPrenom->text().isEmpty() && !(ui->editNom->text().isEmpty()))   // si Champ PRENOM vide
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editPrenom->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
        ui->editNom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"Prénom\" est obligatoire.") );
    }
    else if(ui->editNom->text().isEmpty() && ui->editPrenom->text().isEmpty())  // si les champs NOM et PRENOM sont vides
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editNom->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editPrenom->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Les champs \"Nom\" et \"Prénom\" sont obligatoires.") );
    }
    else
    {
        // On joue le son du bouton
        SoundPlayer::PlayButtonSound();

        if(!ModeAjout)
        {
            FicheContact contact = gc.GetContact(idContactSelectionne);
            contact.setNom(ui->editNom->text().toStdString());
            contact.setPrenom(ui->editPrenom->text().toStdString());
            contact.setEntreprise(ui->editEntreprise->text().toStdString());
            contact.setMail(ui->editMail->text().toStdString());
            contact.setTelephone(ui->editTelephone->text().toStdString());
            contact.setPhoto(ui->ChooseImage->icon().pixmap(ui->ChooseImage->iconSize()).toImage());
            gc.ModifyContact(contact);
        }
        else
        {
            std::string nom = ui->editNom->text().toStdString();
            std::string prenom = ui->editPrenom->text().toStdString();
            std::string entreprise = ui->editEntreprise->text().toStdString();
            std::string mail = ui->editMail->text().toStdString();
            std::string telephone = ui->editTelephone->text().toStdString();
            QImage image = ui->ChooseImage->icon().pixmap(ui->ChooseImage->iconSize()).toImage();
            gc.AddContact(nom,prenom,entreprise,mail,telephone,image);
        }
        this->DisplayContactList();
        this->RefreshLog();
        ui->editNom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        ui->editPrenom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        ui->frameEditContact->setVisible(0);
    }
}

/**
 * @brief Méthode permettant du supprimer le contact séléctionné a partir du bouton
 *
 * Méthode effectuée à la suite de l'appuis sur le bouton supprimer de la MainWindow.
 * Le contact actuellement sélectionné sera donc supprimé de la classe GestionContact.
 * @author Samuel LACHAUD
 */
void MainWindow::SupprimerContact()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    if(gc.GetAllContacts().size() > 0 && !ModeAjout)
    {
        gc.SupprContact(idContactSelectionne);
        ui->frameEditContact->setVisible(0);
        this->DisplayContactList();
        this->RefreshLog();
    }
}

/**
 * @brief Permet de changer l'image d'un contact par appui sur celui-ci par ouverture d'un popup.
 *
 * Cette méthode est effectuée suite à l'appuis sur l'icone de contact d'un utilisateur.
 * Un popup système apparaitra donc permettant à l'utiliser de sélectionner un fichier dans sa machine afin de l'uploader dans l'application.
 * @author Samuel LACHAUD
 */
void MainWindow::ChooseImage()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));

    if(!fileName.isEmpty())
    {
        QPixmap image = QPixmap::fromImage(QImage(fileName));        
        QIcon buttonIcon(image);
        ui->ChooseImage->setIcon(buttonIcon);
        ui->ChooseImage->setIconSize(ui->ChooseImage->size());
    }
}

/**
 * @brief Slot permettant de mettre à jour le contact après édition de ses interactions
 *
 * Ce slot permet de retourner le contact que l'on a envoyé a la fenêtre d'interactions.
 * @param[in] contact auquel on a modifié les interactions.
 * @author Loïs PAZOLA
 */
void MainWindow::ReceiveContactToMainWindow(FicheContact contact)
{
    this->gc.ModifyContact(contact);
}

/**
 * @brief Slot permettant de mettre a jour les logs avec l'ajout, suppression ou modification d'une interaction
 *
 * Slot permettant de mettre a jour les logs avec l'ajout, suppression ou modification d'une interaction.
 * @param[in] str ligne à rajouter aux logs
 * @author Samuel LACHAUD
 */
void MainWindow::AddOperationToLog(std::string str)
{
    this->gc.getLog().AddToTabLog(str);
    this->RefreshLog();
}

/**
 * @brief Slot permettant de recevoir une liste de contact modifiée par les filtres
 *
 * Slot permettant de recevoir une liste de contact modifiée par les filtres et de l'afficher dans la liste de la MainWindow
 * @param[in] listContact  liste de contacts modifiée par les filtres
 * @author Samuel LACHAUD
 */
void MainWindow::ReceiveFromFilterContact(std::vector<FicheContact> listContact)
{
    ui->BFilterContact->setStyleSheet("QPushButton {background-color:red;}");

    ui->ContactList->clear();
    for(FicheContact c : listContact)
    {
        QString str = QString::fromStdString(c.ToString());
        QListWidgetItem* item = new QListWidgetItem(str);
        QVariant v;
        v.setValue(c.getId());
        item->setData(Qt::UserRole, v);
        ui->ContactList->addItem(item);
    }

    //Cache l'édition si le contact est filtré
    bool contactFiltre = true;
    for (int row = 0; row < ui->ContactList->count(); row++){
        QListWidgetItem* item = ui->ContactList->item(row);

        //Si le dernier id sélectionné est trouvé dans la liste des contacts après filtrage
        if (item->data(Qt::UserRole).value<int>() == idContactSelectionne) {
            item->setSelected(true);
            contactFiltre = false;
            break;
        }
    }
    if (contactFiltre) {
        ui->frameEditContact->setVisible(0);
        ui->editNom->clear();
        ui->editPrenom->clear();
        ui->editEntreprise->clear();
        ui->editMail->clear();
        ui->editTelephone->clear();
        idContactSelectionne = -1;
    }

    this->setWindowTitle("Projet de CDAA - Groupe R (FILTRAGE ACTIVÉ)");
}

/**
 * @brief Permet de retirer les filtres de recherche et de revenir à la liste par défaut
 *
 * Cette méthode permet de retirer les filtres de la liste de contacts de la MainWindow et de revenir à la liste de contacts par défaut.
 * @author Loïs PAZOLA
 */
void MainWindow::resetFilters()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    ui->BFilterContact->setStyleSheet("");
    this->DisplayContactList();
    this->ReselectSelectedContact();

    this->setWindowTitle("Projet de CDAA - Groupe R");
}

/**
 * @brief Récupère le GestionContact envoyé par la fenêtre SaveGestionContact
 *
 * Slot permettant de récupérer la classe GestionContact importée depuis un fichier JSON dans la fenêtre SaveGestionContact et de remplacer la classe existante.
 * @param[in] gc    GestionContact à importer
 * @author Loïs PAZOLA
 */
void MainWindow::getGcFromSaveGestionContact(GestionContact gc)
{
    this->gc = gc;

    //Il faut réinitialiser la base de données avec le nouveau GestionContact
    DatabaseStorage::ReinitializeBDD(this->gc);

    //Rafraichissement de la fenêtre
    ui->frameEditContact->setVisible(0);
    this->DisplayContactList();
    this->RefreshLog();
    ui->editNom->clear();
    ui->editPrenom->clear();
    ui->editEntreprise->clear();
    ui->editMail->clear();
    ui->editTelephone->clear();
    idContactSelectionne = -1;
}

/**
 * @brief Resélectionne un contact avec la variable de classe \p idContactSelectionne
 *
 * Méthode permettant de resélectionner le contact  précédemment sélectionné après retrait du filtre
 * @author Loïs PAZOLA
 */
void MainWindow::ReselectSelectedContact(){

    //Boucle pour chaque contact dans la liste des contacts
    for (int row = 0; row < ui->ContactList->count(); row++){
        QListWidgetItem* item = ui->ContactList->item(row);

        //Si l'id correspond au dernier id sélectionné
        if (item->data(Qt::UserRole).value<int>() == idContactSelectionne) {
            item->setSelected(true);
            break;
        }
    }
}

/**
 * @brief Override de la méthode appelée lors d'une demande de fermeture de la fenêtre
 *
 * Redéfinition de la méthode de fermeture de la fenêtre afin d'appliquer le son du bouton et la fermeture de la base de données (fermeture de l'application).
 * @param[out] event     Event de fermeture de la fenêtre
 * @author Loïs PAZOLA
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    // On ferme la base de données
    DatabaseStorage::CloseBDD();

    //event->ignore();  //Empêche la fermeture de la fenêtre
    //event->accept();  //Ré-autorise la fermeture de la fenêtre si ignore() appelé
}
