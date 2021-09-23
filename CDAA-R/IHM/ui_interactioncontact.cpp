/**
 * @file IHM/ui_interactioncontact.cpp
 * @brief Permet de gèrer l'ajout ou la suppression d'une interaction d'un contact
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 23/09/2021
 */

#include "ui_interactioncontact.h"
#include "ui_ui_interactioncontact.h"

/**
 * @brief Constructeur de UI_InteractionContact
 * @param[ou] parent    QWidget de création de classe
 */
UI_InteractionContact::UI_InteractionContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_InteractionContact)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de UI_InteractionContact
 */
UI_InteractionContact::~UI_InteractionContact()
{
    delete ui;
}

/**
 * @brief Methode liée au bouton permettant de valider la liste des intégrations
 * @todo A PROGRAMMER
 */
void UI_InteractionContact::ButtonValidate()
{
    //TODO
}

/**
 * @brief Methode liée au bouton permettant d'annuler l'ajout et de fermer la fenêtre
 * @todo A PROGRAMMER
 */
void UI_InteractionContact::ButtonCancel()
{
    this->~UI_InteractionContact();
}

/**
 * @brief Methode liée au bouton permettant d'ajouter une interaction à un contact
 * @todo A PROGRAMMER
 */
void UI_InteractionContact::ButtonAddInteraction()
{
    //TODO
}

/**
 * @brief Methode liée au bouton permettant de supprimer l'ajout une interaction d'un contact
 * @todo A PROGRAMMER
 */
void UI_InteractionContact::ButtonRemoveInteraction()
{
    //TODO
}

/**
 * @brief Methode liée au bouton permettant de valider l'ajout d'une interaction
 * @todo A PROGRAMMER
 */
void UI_InteractionContact::ButtonValidateInteraction()
{
    //TODO
}
