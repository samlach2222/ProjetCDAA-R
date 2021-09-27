/**
 * @file IHM/mainwindow.cpp
 * @brief Fenêtre principale de l'application permettant d'afficher les contacts, leur édition et toutes les autres actions souhaitées
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
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
#include <qlist.h>

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
    // DEBUT TEST
    FicheContact fc = FicheContact("LACHAUD","Samuel","UFR","sampletext@gmail.com","06060606",QImage());
    gc.AddContact(fc);
    // FIN TEST

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

    this->RefreshLog();
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

void MainWindow::OpenFC()
{
    if(!(rc.isVisible() || sgc.isVisible())){
        fc.show();
    }
}

void MainWindow::OpenRC()
{
    if(!(fc.isVisible() || sgc.isVisible())){
        rc.show();
    }
}

void MainWindow::OpenSGC()
{
    if(!(fc.isVisible() || rc.isVisible())){
        sgc.show();
    }
}

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
    ic.show();
}

void MainWindow::LogsDoubleClick()  // disable Logs edition
{
    ui->LogsList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
