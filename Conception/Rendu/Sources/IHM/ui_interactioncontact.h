/**
 * @file IHM/ui_interactioncontact.h
 * @brief Fichier header pour la fenêtre de gestion des interactions d'un contact
 * @author Samuel LACHAUD
 */
#ifndef UI_INTERACTIONCONTACT_H
#define UI_INTERACTIONCONTACT_H

#include <QWidget>

#include <LOGIC/fichecontact.h>
#include <LOGIC/gestioncontact.h>
#include <LOGIC/interaction.h>

namespace Ui {
class UI_InteractionContact;
}

/**
 * @brief Classe pour la fenêtre de gestion des interactions d'un contact
 *
 * Cette classe est ouverte depuis la MainWindow par doube-clic sur un contact dans la liste.
 * Elle permet d'ajouter, supprimer ou modifier les interactions du contact sélectionné.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
class UI_InteractionContact : public QWidget
{
    Q_OBJECT

public:
    explicit UI_InteractionContact(QWidget *parent = nullptr);
    ~UI_InteractionContact();

private:
    Ui::UI_InteractionContact *ui;
    int id;
    FicheContact contact;
    void DisplayInteractionList();
    void addTags(Interaction*);
    void closeEvent(QCloseEvent*);

public slots:
    void AddInteraction();
    void SupprimerInteraction();
    void ListItemSelected();
    void ValiderInteraction();
    void ReceiveIdToInteraction(int,GestionContact);

signals :
    /**
     * @brief Signal permettant de renvoyer le contact vers le MainWindow
     *
     * Ce signal permet de renvoyer la fiche contact à laquelle on a ajouter/supprimé/modifié une/des intéraction(s)
     * @author Loïs PAZOLA
     */
    void sendContactToMainWindow(FicheContact);

    /**
     * @brief Signal permettant d'envoyer les modifications, ajout et suppression d'interaction vers les logs
     *
     * Ce signal permet d'actualiser la liste des logs affichée sur la MainWindow après avoir ajouter/supprimé/modifié une/des intéraction(s)
     * @author Samuel LACHAUD
     */
    void AddOperationToLog(std::string);
};


#endif // UI_INTERACTIONCONTACT_H
