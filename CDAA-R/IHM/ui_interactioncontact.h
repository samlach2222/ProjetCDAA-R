/**
 * @file IHM/ui_interactioncontact.h
 * @brief Fichier header pour la fenêtre de gestion des intéractions d'un contact
 * @author Samuel LACHAUD
 */

#ifndef UI_INTERACTIONCONTACT_H
#define UI_INTERACTIONCONTACT_H

#include <QWidget>

#include <LOGIC/interaction.h>
#include <LOGIC/gestioncontact.h>

namespace Ui {
class UI_InteractionContact;
}

class UI_InteractionContact : public QWidget
{
    Q_OBJECT

public:
    explicit UI_InteractionContact(QWidget *parent = nullptr);
    ~UI_InteractionContact();
    void SetId(int);
    int GetId();

private:
    Ui::UI_InteractionContact *ui;
    int id;
    FicheContact contact;
    void DisplayInteractionList();

public slots:
    void ValidateAllInteractions();
    void AddInteraction();
    void SupprimerInteraction();
    void ListItemClick();
    void ValiderInteraction();
    void ReceiveIdToInteraction(int,GestionContact);

signals :
    void sendContactToMainWindow(FicheContact);
    void AddOperationToLog(std::string);
};


#endif // UI_INTERACTIONCONTACT_H
