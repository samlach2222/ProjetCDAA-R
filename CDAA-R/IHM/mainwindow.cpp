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
#include "LOGIC/fichecontact.h"
#include "ui_interactioncontact.h"

#include <QStandardItemModel>
#include <QString>
#include <QStringListModel>
#include <QVector>
#include <QPixmap>
#include <QFileDialog>



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

    gc = GestionContact();
    this->RefreshLog();

    // Desactivations de l'édition de contact
    ui->frameEditContact->setVisible(0);
    ui->ChooseImage->setStyleSheet("QPushButton { background-color: rgba(10, 0, 0, 0); }");
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
    ModeAjout = 1;
    ui->frameEditContact->setVisible(1);
    ui->editDateCreation->setDisabled(1);
    this->RefreshLog();
}

/**
 * @brief Méthode pour rafraichir l'affichage de la liste des contacts
 */
void MainWindow::DisplayContactList()
{
    QStringListModel* model = new QStringListModel(this);
    QStringList list;
    int tabSize = gc.GetAllContacts().size();
    for(int i =0; i < static_cast<int>(tabSize); i++)
    {
        QString text = QString::fromStdString(gc.GetAllContacts()[i].ToString());
        list.append(text);
    }
    model->setStringList(list);
    ui->ContactList->setModel(model);
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
    QModelIndexList list =ui->ContactList->selectionModel()->selectedIndexes();

    QStringList slist;
    foreach(const QModelIndex &index, list)
    {
        slist.append( index.data(Qt::DisplayRole ).toString());
    }
    QString qRow = slist[0];
    std::string row = qRow.toUtf8().constData(); // QString to string
    std::string rowId = row.substr(0, 1); // Get Id of row
    int id = std::stoi(rowId);

    // Il manque le fait de passer l'id a la nouvelle fenêtre
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
    QModelIndexList list =ui->ContactList->selectionModel()->selectedIndexes();

    QStringList slist;
    foreach(const QModelIndex &index, list)
    {
        slist.append( index.data(Qt::DisplayRole ).toString());
    }
    QString qRow = slist[0];
    std::string row = qRow.toUtf8().constData(); // QString to string
    std::string rowId = row.substr(0, 1); // Get Id of row
    int id = std::stoi(rowId);
    FicheContact contact = gc.GetContact(id -1);

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
    if(!ModeAjout)
    {
        QModelIndexList list =ui->ContactList->selectionModel()->selectedIndexes();
        QStringList slist;
        foreach(const QModelIndex &index, list)
        {
            slist.append( index.data(Qt::DisplayRole ).toString());
        }
        QString qRow = slist[0];
        std::string row = qRow.toUtf8().constData(); // QString to string
        std::string rowId = row.substr(0, 1); // Get Id of row
        int id = std::stoi(rowId);
        FicheContact contact = gc.GetContact(id -1);
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
        FicheContact contact = FicheContact(nom,prenom,entreprise,mail,telephone,image);
        gc.AddContact(contact);
    }
    this->DisplayContactList();
    this->RefreshLog();
}

/**
 * @brief Méthode permettant du supprimer le contact séléctionné a partir du bouton
 */
void MainWindow::SupprimerContact()
{
    QModelIndexList list =ui->ContactList->selectionModel()->selectedIndexes();

    QStringList slist;
    foreach(const QModelIndex &index, list)
    {
        slist.append( index.data(Qt::DisplayRole ).toString());
    }
    QString qRow = slist[0];
    std::string row = qRow.toUtf8().constData(); // QString to string
    std::string rowId = row.substr(0, 1); // Get Id of row
    int id = std::stoi(rowId);
    gc.SupprContact(id - 1);
    this->DisplayContactList();
    ui->frameEditContact->setVisible(0);
    this->RefreshLog();

}

/**
 * @brief Permet de changer l'image d'un contact par appui sur celui-ci
 */
void MainWindow::ChooseImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));

    QPixmap image = QPixmap::fromImage(QImage(fileName));
    int w = ui->Image->width();
    int h = ui->Image->height();
    ui->Image->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
}
