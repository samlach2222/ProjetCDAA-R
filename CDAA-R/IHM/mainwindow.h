/**
 * @file IHM/mainwindow.h
 * @brief Fichier header pour la fenêtre principale de l'application
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../LOGIC/fichecontact.h"
#include "../LOGIC/gestioncontact.h"
#include "ui_filtercontact.h"
#include "ui_interactioncontact.h"
#include "ui_requestcontact.h"
#include "ui_savegestioncontact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Classe pour la fenêtre principale de l'application
 */
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
    int idContactSelectionne;

    void DisplayContactList();
    void RefreshLog();
    int GetIdFromRow(std::string);
    void closeEvent(QCloseEvent*);
    void resetFilters();
    void ReselectSelectedContact();

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
    void ReceiveContactToMainWindow(FicheContact);
    void AddOperationToLog(std::string);
    void ReceiveFromFilterContact(std::vector<FicheContact>);
    void getGcFromSaveGestionContact(GestionContact);

signals :
    /**
     * @brief Signal permettant d'envoyer l'id du contact auquel on met des interaction, ainsi que la classe de gestion de contacts
     */
    void sendIdToInteraction(int,GestionContact);

    /**
     * @brief Signal permettant d'envoyer la classe de gestion de contact à la classe FilterContact
     */
    void sendToFilterContact(GestionContact);

    /**
     * @brief Envoie le GestionContact à la fenêtre SaveGestionContact
     */
    void sendGcToSaveGestionContact(GestionContact);

    /**
     * @brief Envoie le GestionContact à la fenêtre RequestContact
     */
    void sendGcToRequestContact(GestionContact);
};
#endif // MAINWINDOW_H
