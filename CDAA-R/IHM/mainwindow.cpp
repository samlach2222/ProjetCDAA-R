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
//#include "LOGIC/gestioncontact.h"
//#include "ui_interactioncontact.h"
#include "LOGIC/soundplayer.h"

#include <QFileDialog>
////#include <QHBoxLayout>
#include <QMessageBox>
#include <QPixmap>
////#include <QStandardItemModel>
#include <QString>
#include <QStringListModel>  //inclus <QtCore/qstringlist.h>
////#include <QVector>

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
    //FIN DEFINITION SIGNAUX

    gc = GestionContact();
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

    QPixmap QPAddContact(":/Ressources/Icons/AddContact.png");
    int wac = ui->BAddContact->width() * 90/100;
    int hac = ui->BAddContact->height() * 90/100;
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
    SoundPlayer s;
    s.PlayButtonSound();

    ModeAjout = 1;
    ui->frameEditContact->setVisible(1);
    ui->editDateCreation->setDisabled(1);
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
    int tabSize = gc.GetLog().getTabLog().size();
    for(int i =0; i < static_cast<int>(tabSize); i++)
    {
        QString text = QString::fromStdString(gc.GetLog().getTabLog()[i]);
        list.append(text);
    }
    model->setStringList(list);
    ui->LogsList->setModel(model);
}

/**
 * @brief Méthode permettant l'ouverte de FilterContact si aucune fenêtre n'est ouverte
 */
void MainWindow::OpenFC()
{
    if(!(rc.isVisible() || sgc.isVisible() || ic.isVisible())){
        fc.show();
    }
}

/**
 * @brief Méthode permettant l'ouverte de RequestContact si aucune fenêtre n'est ouverte
 */
void MainWindow::OpenRC()
{
    if(!(fc.isVisible() || sgc.isVisible() || ic.isVisible())){
        rc.show();
    }
}

/**
 * @brief Méthode permettant l'ouverte de SaveGestionContact si aucune fenêtre n'est ouverte
 */
void MainWindow::OpenSGC()
{
    if(!(fc.isVisible() || rc.isVisible() || ic.isVisible())){
        sgc.show();
    }
}

/**
 * @brief Méthode liée au double clic sur un contact permettant l'ouverture de la fiche d'intéraction, si aucune fenêtre n'est ouverte
 */
void MainWindow::ListItemDoubleClick()
{
    QList<QListWidgetItem*> selectedItem = ui->ContactList->selectedItems();
    QVariant v = selectedItem[0]->data(Qt::UserRole);
    int idContact = v.value<int>();

    FicheContact contact = gc.GetContact(idContact);

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

    ModeAjout = 0;
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
    ui->Image->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
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
        SoundPlayer s;
        s.PlayErrorSound();
        ui->editNom->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editPrenom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"nom\" est obligatoire.") );

    }
    else if(ui->editPrenom->text().isEmpty() && !(ui->editNom->text().isEmpty()))   // si Champ PRENOM vide
    {
        ui->editPrenom->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
        ui->editNom->setStyleSheet("QLineEdit {border-style: solid; border-width: 1px; border-color: #7A7A7A;}");
        QMessageBox::warning(this, tr("Erreur champs"), tr("Le champ \"prénom\" est obligatoire.") );
    }
    else if(ui->editNom->text().isEmpty() && ui->editPrenom->text().isEmpty())  // si les champs NOM et PRENOM sont vides
    {
        ui->editNom->setStyleSheet("QLineEdit {border-style: outset; border-width: 2px; border-color: red;}");
        ui->editPrenom->setStyleSheet("QLineEdit { border-style: outset; border-width: 2px; border-color: red;}");
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
    }
}

/**
 * @brief Méthode permettant du supprimer le contact séléctionné a partir du bouton
 */
void MainWindow::SupprimerContact()
{
    if(gc.GetAllContacts().size() > 0 && !ModeAjout)
    {
        QList<QListWidgetItem*> selectedItem = ui->ContactList->selectedItems();
        QVariant v = selectedItem[0]->data(Qt::UserRole);
        int idContact = v.value<int>();

        gc.SupprContact(idContact);
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
 * @param contact
 */
void MainWindow::ReceiveContactToMainWindow(FicheContact contact)
{
    this->gc.ModifyContact(contact);
}

/**
 * @brief Slot permettant de mettre a jour les logs avec l'ajout, suppression ou modification d'une interaction
 * @param str
 */
void MainWindow::AddOperationToLog(std::string str)
{
    this->gc.GetLog().AddToTabLog(str);
    this->RefreshLog();
}
