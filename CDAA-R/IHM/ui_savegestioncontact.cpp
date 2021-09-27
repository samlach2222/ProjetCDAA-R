/**
 * @file IHM/ui_savegestioncontact.cpp
 * @brief Permet l'import et l'export des informations au format JSON
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 23/09/2021
 */

#include "ui_savegestioncontact.h"
#include "ui_ui_savegestioncontact.h"
#include "STORAGE/jsonstorage.h"

/**
 * @brief Constructeur de UI_SaveGestionContact
 * @param[out] parent    QWidget de création de classe
 * @param[out] gestionContact    Pointer vers la valuer de la classe GestionContact pour en modifier la valeur en import
 */
UI_SaveGestionContact::UI_SaveGestionContact(QWidget *parent, GestionContact *gestionContact) :
    QWidget(parent),
    ui(new Ui::UI_SaveGestionContact)
{
    ui->setupUi(this);
    this->gc = gestionContact; // On récupère la valeur de gestionContact
    this->jss = JSonStorage("Save.json");
}

/**
 * @brief Destructeur de UI_SaveGestionContact
 */
UI_SaveGestionContact::~UI_SaveGestionContact()
{
    delete ui;
}

/**
 * @brief Méthode d'import des données pour modifier le paramètre de classe **gestioncontact**
 */
void UI_SaveGestionContact::Import()
{
    *gc = this->jss.Load();
    // ON DOIT EXPORTER MAINENANT LA CLASSE GC
}

/**
 * @brief Méthode d'export des données contenues dans le paramètre de classe **gestioncontact**
 */
void UI_SaveGestionContact::Export()
{
    this->jss.Save(*gc);
}

/**
 * @brief Méthode assignée au bouton **Annuler** qui permet de revenir en arrière sur la page précédente
 */
void UI_SaveGestionContact::Annuler()
{
    this->~UI_SaveGestionContact();
}