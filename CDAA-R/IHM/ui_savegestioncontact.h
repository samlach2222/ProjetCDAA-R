/**
 * @file IHM/ui_savegestioncontact.h
 * @brief Fichier header pour l'import export des données en Json depuis l'interface graphique
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
#ifndef UI_SAVEGESTIONCONTACT_H
#define UI_SAVEGESTIONCONTACT_H

#include <QWidget>

#include "STORAGE/jsonstorage.h"  //Inclus LOGIC/gestioncontact.h

namespace Ui {
class UI_SaveGestionContact;
}

class UI_SaveGestionContact : public QWidget
{
    Q_OBJECT

public:
     UI_SaveGestionContact(QWidget *parent = nullptr, GestionContact *gestionContact = nullptr);
    ~UI_SaveGestionContact();

private:
    Ui::UI_SaveGestionContact *ui;
    JSonStorage jss = JSonStorage("Save.json");
    GestionContact* gc;


public slots:
    void Import();
    void Export();
    void Fermer();
};
#endif // UI_SAVEGESTIONCONTACT_H
