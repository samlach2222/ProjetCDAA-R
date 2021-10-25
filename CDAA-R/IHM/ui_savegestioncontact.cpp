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

#include "../LOGIC/soundplayer.h"
#include "../STORAGE/jsonstorage.h"

/**
 * @brief Constructeur de UI_SaveGestionContact
 * @param[out] parent    QWidget de création de classe
 * @param[out] gestionContact    Pointer vers la valeur de la classe GestionContact pour en modifier la valeur en import ou l'exporter
 */
UI_SaveGestionContact::UI_SaveGestionContact(QWidget *parent, GestionContact *gestionContact) :
    QWidget(parent),
    ui(new Ui::UI_SaveGestionContact)
{
    ui->setupUi(this);
    this->gc = gestionContact; // On récupère la valeur de gestionContact
}

/**
 * @brief Destructeur de UI_SaveGestionContact
 */
UI_SaveGestionContact::~UI_SaveGestionContact()
{
    delete ui;
    delete gc;
}

/**
 * @brief Override de la méthode appelée lors d'une demande de fermeture de la fenêtre
 * @param event     Event de fermeture de la fenêtre
 */
void UI_SaveGestionContact::closeEvent(QCloseEvent *event)
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    //event->ignore();  //Empêche la fermeture de la fenêtre
    //event->accept();  //Ré-autorise la fermeture de la fenêtre si ignore() appelé
}

/**
 * @brief Méthode d'import des données pour modifier le paramètre de classe **gestioncontact**
 * @todo Exporter le GestionContact dans le mainwindow
 */
void UI_SaveGestionContact::Import()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    GestionContact gc = JSonStorage::Load();

    //Ne pas charger si le fichier n'existait pas ou était vide
    if (gc.GetAllContacts().size() == 0 && gc.GetLog().getTabLog().size() == 0){
        ui->informationLabel->setText("Fichier inexistant ou vide");
        return;
    }

    this->gc = &gc;
    // ON DOIT EXPORTER MAINENANT LA CLASSE GC

    ui->informationLabel->setText("Import effectué");
}

/**
 * @brief Méthode d'export des données contenues dans le paramètre de classe **gestioncontact**
 */
void UI_SaveGestionContact::Export()
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

//    GestionContact gc0;
//    gc = &gc0;
//    gc->AddContact("LACHAUD","Samuel","UFR","sampletext@gmail.com","06060606",QImage("..\\Programs\\logo.png"));
//    gc->AddContact("LACHAUD","Samuel","UFR","sampletext@gmail.com","06060606",QImage("..\\Programs\\logo.png"));
//    gc->GetLog().AddToTabLog("log 0");
//    gc->GetLog().AddToTabLog("log 1");
//    gc->GetContact(0).AddInteraction("Préparer la raclette\n@todo Cuire les pommes de terres\n@todo Digérer @date 10/11/2021","Manger de la raclette");
    JSonStorage::Save(*gc);

    ui->informationLabel->setText("Export effectué");
}
