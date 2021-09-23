/**
 * @file IHM/ui_requestcontact.cpp
 * @brief Permet de gèrer les requêtes à la base de donnée sur la liste de contacts
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 23/09/2021
 */

#include "ui_requestcontact.h"
#include "ui_ui_requestcontact.h"

/**
 * @brief Constructeur de UI_RequestContact
 * @param[ou] parent    QWidget de création de classe
 */
UI_RequestContact::UI_RequestContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_RequestContact)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de UI_RequestContact
 */
UI_RequestContact::~UI_RequestContact()
{
    delete ui;
}

/**
 * @brief Méthode liée au bouton permettant d'effectuer la requête choisie
 * @todo A PROGRAMMER
 */
void UI_RequestContact::ButtonDoRequest()
{
    //TODO
}

/**
 * @brief Méthode du bu=outon permettant d'annuler la page de requête et de la fermer
 */
void UI_RequestContact::ButtonCancel()
{
    this->~UI_RequestContact();
}
