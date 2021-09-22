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

    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(AddContact()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddContact()
{
    FicheContact fc = FicheContact("LACHAUD","Samuel","UFR","sampletext@gmail.com","06060606",QImage());
    gc.AddContact(fc);

    ui->listView->setModel(new QStringListModel());
}

