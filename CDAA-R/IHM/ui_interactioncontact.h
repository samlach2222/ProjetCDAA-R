/**
 * @file IHM/ui_interactioncontact.h
 * @brief Fichier header pour la fenêtre de gestion des intéractions d'un contact
 * @author Samuel LACHAUD
 */

#ifndef UI_INTERACTIONCONTACT_H
#define UI_INTERACTIONCONTACT_H

#include <QWidget>

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

public slots:
    void ButtonValidate();
    void ButtonCancel();
    void ButtonAddInteraction();
    void ButtonRemoveInteraction();
    void ButtonValidateInteraction();
    void ReceiveIdToInteraction(int);
};

#endif // UI_INTERACTIONCONTACT_H
