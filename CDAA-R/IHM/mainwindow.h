/**
 * @file IHM/mainwindow.h
 * @brief Fichier header pour la fenêtre principale de l'application
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <LOGIC/fichecontact.h>
#include <LOGIC/gestioncontact.h>
#include "ui_filtercontact.h"
#include "ui_interactioncontact.h"
#include "ui_requestcontact.h"
#include "ui_savegestioncontact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Classe pour la fenêtre principale de l'application
 *
 * Cette classe est la classe exécutant la fenêtre principale de l'application, elle permet d'avoir accès a la liste de contacts.
 * Elle permet également d'ouvrir les différentes fenêtres et de montrer les logs de l'application.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
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
    UI_FilterContact *fc;
    UI_RequestContact *rc;
    UI_SaveGestionContact *sgc; // Not StarGate Command
    UI_InteractionContact *ic;
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
    void ListItemSelected();
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
     *
     * Ce signal permet d'envoyer l'id du conatct auquel on veut rajouter des interactions afin de connaitre à quel contact on doit rajouter l'interaction
     * On envoie également la classe de gestion de contacts afin de pouvoir connaitre le contact a qui l'on ajoute une interaction.
     * @author Loïs PAZOLA
     */
    void sendIdToInteraction(int,GestionContact);

    /**
     * @brief Signal permettant d'envoyer la classe de gestion de contact à la classe FilterContact
     *
     * Ce signal permet d(envoyer la classe de gestion de contact à la classe permettant de filtrer les contacts.
     * En effet à partir de la classe de Gestion de contacts, on va récupérer la liste des contacts et les trier comme on veux.
     * @author Samuel LACHAUD
     */
    void sendToFilterContact(GestionContact);

    /**
     * @brief Rafraichit la liste des contacts filtrés
     *
     * Ce signal permet de rafraichir la liste des contacts depuis la classe de gestion de contacts.
     * On peux ainsi récupérer la liste originale sans filtres.
     * @author Loïs PAZOLA
     */
    void refreshFilteredContacts(GestionContact);

    /**
     * @brief Envoie le GestionContact à la fenêtre SaveGestionContact
     *
     * Ce signal permet d'envoyer la classe de gestion de contact à la classe de sauvegarde JSON.
     * On peux ainsi la modifier à partir d'un fichier JSON externe ou alors sauvegarde celle-ci dans un fichier JSON.
     * @author Loïs PAZOLA
     */
    void sendGcToSaveGestionContact(GestionContact);

    /**
     * @brief Envoie le GestionContact à la fenêtre RequestContact
     *
     * Ce signal permet d'envoyer la classe de gestion de contact à la classe effectuant des requêtes sur la base de donnée.
     * La classe de requêtes pourra donc donner à l'utilisateur, graphiquement une liste de contacts pour qu'il puisse choisir le contact visé par la requête.
     * @author Samuel LACHAUD
     */
    void sendGcToRequestContact(GestionContact);
};
#endif // MAINWINDOW_H
