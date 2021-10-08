/**
 * @file IHM/ui_filtercontact.cpp
 * @brief Permet d'appliquer des filtres sur une recherche de contacts
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 23/09/2021
 */

#include "ui_filtercontact.h"
#include "ui_ui_filtercontact.h"

/**
 * @brief Constructeur de UI_FilterContact
 * @param[out] parent   QWidget de création de classe
 */
UI_FilterContact::UI_FilterContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_FilterContact)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de UI_FilterContact
 */
UI_FilterContact::~UI_FilterContact()
{
    delete ui;
}

/**
 * @brief Permet de valider le filtre à partir du bouton lié
 * @todo A PROGRAMMER
 */
void UI_FilterContact::ButtonValidate()
{
    //TODO
}

/**
 * @brief Permet d'annuler le filtre et de fermer la fenêtre
 */
void UI_FilterContact::ButtonCancel()
{
    this->~UI_FilterContact();
}
