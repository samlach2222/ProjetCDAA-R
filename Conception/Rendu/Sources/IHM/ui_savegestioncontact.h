/**
 * @file IHM/ui_savegestioncontact.h
 * @brief Fichier header pour l'import et export des données en Json depuis l'interface graphique
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
#ifndef UI_SAVEGESTIONCONTACT_H
#define UI_SAVEGESTIONCONTACT_H

#include <QWidget>

#include <LOGIC/gestioncontact.h>

namespace Ui {
class UI_SaveGestionContact;
}

/**
 * @brief Classe pour l'import et export des données en Json depuis l'interface graphique
 *
 * Cette classe est ouvert par l'appui d'un bouton sur la MainWindow.
 * Elle permet d'importer/exporter les données de l'application au format JSON.
 * @author Loïs PAZOLA
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
     *
     * Ce signal permet de renvoyer au MainWindow la classe de GestionContact que l'on a remplie à l'aide du fichier JSON exter à l'application
     * Il permet donc l'import de données vers l'application.
     * @author Loïs PAZOLA
     */
    void sendGcToMainWindow(GestionContact);
};
#endif // UI_SAVEGESTIONCONTACT_H
