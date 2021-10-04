/**
 * @file IHM/mainwindow.h
 * @brief Fichier header pour la fenêtre principale de l'application
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "LOGIC/gestioncontact.h"
#include "LOGIC/log.h"
#include "ui_filtercontact.h"
#include "ui_requestcontact.h"
#include "ui_savegestioncontact.h"
#include "ui_interactioncontact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GestionContact gc;
    UI_FilterContact fc;
    UI_RequestContact rc;
    UI_SaveGestionContact sgc; // Not StarGate Command
    UI_InteractionContact ic;

    void DisplayContactList();
    void RefreshLog();
    int GetIdFromRow(std::string row);

public slots:
    void AddContact();
    void OpenFC();
    void OpenRC();
    void OpenSGC();
    void ListItemDoubleClick();
    void LogsDoubleClick();
    void ListItemClick();
    void ValiderContact();
    void SupprimerContact();
    void ChooseImage();

signals :
    void sendIdToInteraction(int, GestionContact);
};
#endif // MAINWINDOW_H
