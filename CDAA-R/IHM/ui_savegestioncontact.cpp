/**
 * @file IHM/ui_savegestioncontact.cpp
 * @brief Permet de gérer l'import et l'export des informations au format JSON
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.2
 * @date 23/09/2021
 */

#include "ui_savegestioncontact.h"
#include "ui_ui_savegestioncontact.h"

#include <LOGIC/soundplayer.h>
#include <STORAGE/jsonstorage.h>

/**
 * @brief Constructeur de UI_SaveGestionContact
 *
 * Constructeur de la fenêtre d'import/export au format JSON des données de l'application.
 * Ce constructeur permet d'initialiser les éléments graphiques de cette fenêtre.
 * @author Loïs PAZOLA
 * @param[out] parent    QWidget de création de classe
 */
UI_SaveGestionContact::UI_SaveGestionContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_SaveGestionContact)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de UI_SaveGestionContact
 *
 * Destructeur de la fenêtre d'import/export des données de l'application.
 * Ce destructeur permet de détruire la fenêtre actuelle avec les différents controlleurs qui lui sont liés.
 * @author Loïs PAZOLA
 */
UI_SaveGestionContact::~UI_SaveGestionContact()
{
    delete ui;
}

/**
 * @brief Override de la méthode appelée lors d'une demande de fermeture de la fenêtre
 *
 * Redéfinition de la méthode de fermeture de la fenêtre afin d'appliquer le son du bouton et la fermeture de la base de données (fermeture de l'application).
 * @param[out] event     Event de fermeture de la fenêtre
 * @author Loïs PAZOLA
 */
void UI_SaveGestionContact::closeEvent(QCloseEvent *event)
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    //event->ignore();  //Empêche la fermeture de la fenêtre
    //event->accept();  //Ré-autorise la fermeture de la fenêtre si ignore() appelé
}

/**
 * @brief Méthode d'import des données pour modifier le paramètre de classe de gestion de contacts
 *
 * Méthode utilisée par le clic sur le bouton associé sur la fenêtre.
 * Celle-ci permet d'importer les données depuis un fichier JSON dans l'application.
 * Les données remplacent donc la classe GestionContact
 * @author Loïs PAZOLA
 */
void UI_SaveGestionContact::Import()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    GestionContact gc = JSonStorage::Load();

    //Ne pas charger si le fichier n'existait pas ou était vide
    if (gc.GetAllContacts().size() == 0 && gc.getLog().getTabLog().size() == 0){
        ui->informationLabel->setText("Fichier inexistant ou vide");
        return;
    }

    this->gc = gc;
    emit sendGcToMainWindow(this->gc);

    ui->informationLabel->setText("Import effectué");
}

/**
 * @brief Méthode d'export des données contenues dans le paramètre de classe de gestion de contacts
 *
 * Méthode utilisée par le clic sur le bouton associé sur la fenêtre.
 * Celle-ci permet d'importer les données depuis un fichier JSON dans l'application.
 * Les données remplacent donc la classe GestionContact
 * @author Loïs PAZOLA
 */
void UI_SaveGestionContact::Export()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    JSonStorage::Save(gc);

    ui->informationLabel->setText("Export effectué");
}

/**
 * @brief Récupère le GestionContact envoyé par le MainWindow
 *
 * Slot permettant de récupérer la classe GestionContact.
 * celle-ci va donc nous permettre d'effectuer l'import des données du fichier JSON vers la classe.
 * @author Loïs PAZOLA
 * @param[in] gc    GestionContact à exporter
 */
void UI_SaveGestionContact::getGcFromMainWindow(GestionContact gc)
{
    this->gc = gc;
}
