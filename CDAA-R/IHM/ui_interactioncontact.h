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

private:
    Ui::UI_InteractionContact *ui;

public slots:
    void ButtonValidate();
    void ButtonCancel();
    void ButtonAddInteraction();
    void ButtonRemoveInteraction();
    void ButtonValidateInteraction();
};

#endif // UI_INTERACTIONCONTACT_H