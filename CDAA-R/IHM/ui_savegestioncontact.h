/**
 * @file IHM/ui_savegestioncontact.h
 * @brief Fichier header pour l'import et export des données en Json depuis l'interface graphique
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
#ifndef UI_SAVEGESTIONCONTACT_H
#define UI_SAVEGESTIONCONTACT_H

#include <QWidget>

#include "../LOGIC/gestioncontact.h"

namespace Ui {
class UI_SaveGestionContact;
}

/**
 * @brief Classe pour l'import et export des données en Json depuis l'interface graphique
 */
class UI_SaveGestionContact : public QWidget
{
    Q_OBJECT

public:
     UI_SaveGestionContact(QWidget *parent = nullptr);
    ~UI_SaveGestionContact();

private:
    void closeEvent(QCloseEvent*);
    Ui::UI_SaveGestionContact* ui;
    GestionContact gc;


public slots:
    void Import();
    void Export();
    void getGcFromMainWindow(GestionContact);

signals:
    /**
     * @brief Envoie le GestionContact au MainWindow
     */
    void sendGcToMainWindow(GestionContact);
};
#endif // UI_SAVEGESTIONCONTACT_H
