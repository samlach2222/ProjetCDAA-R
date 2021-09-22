#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LOGIC/fichecontact.h"


#include <QStandardItemModel>
#include <QString>
#include <QStringListModel>
#include <QVector>
#include <qlist.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gc = GestionContact();
    this->RefreshLog();
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    ui->listView->setModel(model);

    this->RefreshLog();
}

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
    ui->listView_2->setModel(model);
}

