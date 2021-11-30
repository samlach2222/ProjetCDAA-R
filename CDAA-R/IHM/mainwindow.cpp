/**
 * @file IHM/mainwindow.cpp
 * @brief Fenêtre principale de l'application permettant d'afficher les contacts, leur édition et toutes les autres actions souhaitées
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.1
 * @date 23/09/2021
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../LOGIC/soundplayer.h"
#include "../STORAGE/databasestorage.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QStringListModel>

/**
 * @brief Valeur booléenne pour savoir si on ajoute un contact ou si on l'édite
 */
bool ModeAjout = 0;


/**
 * @brief Constructeur de mainwindows
 * @param[out] parent    QWidget de création de classe
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // DEBUT DEFINITION SIGNAUX
    QObject::connect(this, SIGNAL(sendIdToInteraction(int,GestionContact)), &ic, SLOT(ReceiveIdToInteraction(int,GestionContact)));
    QObject::connect(&ic, SIGNAL(sendContactToMainWindow(FicheContact)), this, SLOT(ReceiveContactToMainWindow(FicheContact)));
    QObject::connect(&ic, SIGNAL(AddOperationToLog(std::string)), this, SLOT(AddOperationToLog(std::string)));
    QObject::connect(this, SIGNAL(sendToFilterContact(GestionContact)), &fc, SLOT(ReceiveFromMainWindow(GestionContact)));
    QObject::connect(&fc, SIGNAL(sendListContactToMainWindow(std::vector<FicheContact>)), this, SLOT(ReceiveFromFilterContact(std::vector<FicheContact>)));
    QObject::connect(this, SIGNAL(sendGcToSaveGestionContact(GestionContact)), &sgc, SLOT(getGcFromMainWindow(GestionContact)));
    QObject::connect(&sgc, SIGNAL(sendGcToMainWindow(GestionContact)), this, SLOT(getGcFromSaveGestionContact(GestionContact)));
    //FIN DEFINITION SIGNAUX

    gc = DatabaseStorage::Load();
    idContactSelectionne = -1;
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
 * @brief Destructeur de mainwindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Méthode associée au bouton d'ajout de contact permettant d'ajouter un contact à la gestion de contact
 */
void MainWindow::AddContact()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    ModeAjout = 1;
    ui->frameEditContact->setVisible(1);
    QPixmap image = QPixmap::fromImage(QImage(":/Ressources/Icons/unknownContact.png"));
    int w = ui->Image->width();
    int h = ui->Image->height();
    ui->Image->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));

    ui->editNom->clear();
    ui->editPrenom->clear();
    ui->editEntreprise->clear();
    ui->editMail->clear();
    ui->editTelephone->clear();

    this->RefreshLog();
}

/**
 * @brief Méthode pour rafraichir l'affichage de la liste des contacts
 */
void MainWindow::DisplayContactList()
{
    ui->ContactList->clear();
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

/**
 * @brief Méthode permettant de rafraichir l'affichage des logs à chaque fois qu'une action est effectuée
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

    //Réinitialise l'id selectionné
    this->idContactSelectionne = -1;
}

/**
 * @brief Méthode permettant l'ouverte de FilterContact si aucune fenêtre n'est ouverte
 */
void MainWindow::OpenFC()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    if (ui->BFilterContact->styleSheet().contains("QPushButton {background-color:red;")){  //Ne pas vérifier le styleSheet avec == au cas où on veuille le modifier plus tard
        this->resetFilters();  //Permet au raccourci clavier de d'abord désactiver le filtrage des contacts si activé
    } else {
        if(!(rc.isVisible() || sgc.isVisible() || ic.isVisible())){
            emit sendToFilterContact(this->gc);
            fc.show();
        }
    }
}

/**
 * @brief Méthode permettant l'ouverte de RequestContact si aucune fenêtre n'est ouverte
 */
void MainWindow::OpenRC()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    if(!(fc.isVisible() || sgc.isVisible() || ic.isVisible())){
        rc.show();
    }
}

/**
 * @brief Méthode permettant l'ouverte de SaveGestionContact si aucune fenêtre n'est ouverte
 */
void MainWindow::OpenSGC()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    if(!(fc.isVisible() || rc.isVisible() || ic.isVisible())){
        emit sendGcToSaveGestionContact(this->gc);
        sgc.show();
    }
}

/**
 * @brief Méthode liée au double clic sur un contact permettant l'ouverture de la fiche d'intéraction, si aucune fenêtre n'est ouverte
 */
void MainWindow::ListItemDoubleClick()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    QList<QListWidgetItem*> selectedItem = ui->ContactList->selectedItems();
    QVariant v = selectedItem[0]->data(Qt::UserRole);
    int idContact = v.value<int>();

    FicheContact contact = gc.GetContact(idContact);

    ic.setWindowTitle("Interactions de "+QString::fromStdString(contact.ToString()));
    emit sendIdToInteraction(idContact,this->gc);
    if(!(fc.isVisible() || rc.isVisible() || sgc.isVisible())){
        ic.show();
    }
}

/**
 * @brief Méthode liée au  clic sur un contact permettant l'édition de celui-ci
 */
void MainWindow::ListItemClick()
{
    QList<QListWidgetItem*> selectedItem = ui->ContactList->selectedItems();
    QVariant v = selectedItem[0]->data(Qt::UserRole);
    if (idContactSelectionne != v.value<int>()){
        // On joue le son du bouton
        SoundPlayer::PlayButtonSound();

        ModeAjout = 0;
        idContactSelectionne = v.value<int>();

        FicheContact contact = gc.GetContact(idContactSelectionne);

        ui->frameEditContact->setVisible(1);

        ui->editNom->setText(QString::fromStdString(contact.getNom()));
        ui->editPrenom->setText(QString::fromStdString(contact.getPrenom()));
        ui->editEntreprise->setText(QString::fromStdString(contact.getEntreprise()));
        ui->editMail->setText(QString::fromStdString(contact.getMail()));
        ui->editTelephone->setText(QString::fromStdString(contact.getTelephone()));

        ui->editDateCreation->setText(QString::fromStdString(contact.getDateCreation().ToString()));

        QPixmap image = QPixmap::fromImage(contact.getPhoto());
        int w = ui->Image->width();
        int h = ui->Image->height();
        ui->Image->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
    }
}

/**
 * @brief Méthode permettant de supprimer l'intéraction des logs
 */
void MainWindow::LogsDoubleClick()  // disable Logs edition
{
    ui->LogsList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

/**
 * @brief Permet de sauvegarder un nouveau contact ou la modification d'un contact déjà existant avec le bouton valider
 */
void MainWindow::ValiderContact()
{
    if(ui->editNom->text().isEmpty() && !(ui->editPrenom->text().isEmpty()))    // si Champ NOM vide
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editNom->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editPrenom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"nom\" est obligatoire.") );

    }
    else if(ui->editPrenom->text().isEmpty() && !(ui->editNom->text().isEmpty()))   // si Champ PRENOM vide
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editPrenom->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
        ui->editNom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"prénom\" est obligatoire.") );
    }
    else if(ui->editNom->text().isEmpty() && ui->editPrenom->text().isEmpty())  // si les champs NOM et PRENOM sont vides
    {
        // On joue le son de l'erreur
        SoundPlayer::PlayErrorSound();

        ui->editNom->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editPrenom->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Les champs \"nom\" et \"prénom\" sont obligatoires.") );
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
    }
}

/**
 * @brief Méthode permettant du supprimer le contact séléctionné a partir du bouton
 */
void MainWindow::SupprimerContact()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    if(gc.GetAllContacts().size() > 0 && !ModeAjout)
    {
        gc.SupprContact(idContactSelectionne);
        this->DisplayContactList();
        ui->frameEditContact->setVisible(0);
        this->RefreshLog();
    }
}

/**
 * @brief Permet de changer l'image d'un contact par appui sur celui-ci par ouverture d'un popup.
 */
void MainWindow::ChooseImage()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));

    if(!fileName.isEmpty())
    {
        QPixmap image = QPixmap::fromImage(QImage(fileName));
        int w = ui->Image->width();
        int h = ui->Image->height();
        ui->Image->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
    }
}

/**
 * @brief Retourne l'id à partir d'une ligne complète
 * @param[in] row       La ligne complète
 * @return l'id obtenu
 */
int MainWindow::GetIdFromRow(std::string row)
{
    //Prend la position du premier charactère ".", et initialise un string à partir du début jusqu'à cette position
    std::size_t posPoint = row.find_first_of(".");
    std::string rowId = row.substr(0, posPoint);

    return std::stoi(rowId);
}

/**
 * @brief Slot permettant de mettre à jour le contact après édition de ses intéractions
 * @param[in] contact
 */
void MainWindow::ReceiveContactToMainWindow(FicheContact contact)
{
    this->gc.ModifyContact(contact);
}

/**
 * @brief Slot permettant de mettre a jour les logs avec l'ajout, suppression ou modification d'une interaction
 * @param[in] str
 */
void MainWindow::AddOperationToLog(std::string str)
{
    this->gc.getLog().AddToTabLog(str);
    this->RefreshLog();
}

/**
 * @brief Slot permettant de recevoir une liste de contact modifiée par les filtres
 * @param[in] listContact  liste de contacts modifiée par les filtres
 */
void MainWindow::ReceiveFromFilterContact(std::vector<FicheContact> listContact)
{
    ui->BFilterContact->setStyleSheet("QPushButton {background-color:red;}");
    ui->ContactList->clear();
    for(FicheContact c :listContact)
    {
        QString str = QString::fromStdString(c.ToString());
        QListWidgetItem* item = new QListWidgetItem(str);
        QVariant v;
        v.setValue(c.getId());
        item->setData(Qt::UserRole, v);
        ui->ContactList->addItem(item);
    }

    this->setWindowTitle("Projet de CDAA - Groupe R (FILTRAGE ACTIVÉ)");
}

/**
 * @brief Permet de retirer les filtres de recherche et de revenir à la liste par défaut
 */
void MainWindow::resetFilters()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    this->DisplayContactList();
    ui->BFilterContact->setStyleSheet("");

    this->setWindowTitle("Projet de CDAA - Groupe R");
}

/**
 * @brief Récupère le GestionContact envoyé par la fenêtre SaveGestionContact
 * @param[in] gc    GestionContact à importer
 */
void MainWindow::getGcFromSaveGestionContact(GestionContact gc)
{
    this->gc = gc;

    //Rafraichissement de la fenêtre
    this->DisplayContactList();
    this->RefreshLog();
}

/**
 * @brief Override de la méthode appelée lors d'une demande de fermeture de la fenêtre
 * @param[out] event     Event de fermeture de la fenêtre
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    //event->ignore();  //Empêche la fermeture de la fenêtre
    //event->accept();  //Ré-autorise la fermeture de la fenêtre si ignore() appelé
}
