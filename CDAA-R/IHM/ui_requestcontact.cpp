/**
 * @file IHM/ui_requestcontact.cpp
 * @brief Permet de gèrer les requêtes à la base de donnée sur la liste de contacts
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 23/09/2021
 */

#include "ui_requestcontact.h"
#include "ui_ui_requestcontact.h"

#include "../LOGIC/soundplayer.h"

#include <QListWidgetItem>

/**
 * @brief Constructeur de UI_RequestContact
 * @param[out] parent    QWidget de création de classe
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
 * @todo Gèrer les indexs de contacts
 */
void UI_RequestContact::ButtonDoRequest()
{
    std::string res = "";
    if(ui->CB_R1->isChecked()){ // CB1 Activé
        res += "R1 : \n" + this->NbContact() + "--------------------\n";
    }

    if(ui->CB_R2->isChecked()){ // CB2 Activé
        res += "R2 : \n" + this->GetAllInteractionsBetweenTwoDates(ui->DE_DateDebutR2->date(), ui->DE_DateFinR2->date()) + "--------------------\n";
    }

    if(ui->CB_R3->isChecked()){ // CB3 Activé
        res += "R3 : \n" + this->GetTagTodoContactBetweenTwoDates(ui->L_ContactR3->currentIndex(),ui->DE_DateDebutR3->date(), ui->DE_DateFinR3->date()) + "--------------------\n"; // gèrer la liste
    }

    if(ui->CB_R4->isChecked()){ // CB4 Activé
        res += "R4 : \n" + this->GetTagTodoContactBetweenTwoDates(ui->L_ContactR4->currentIndex(),ui->DE_DateDebutR4->date(), ui->DE_DateFinR4->date()) + "--------------------\n";
    }

    if(ui->CB_R5->isChecked()){ // CB5 Activé
        res += "R5 : \n" + this->GetTagTodoAllContactBetweenTwoDates(ui->DE_DateDebutR5->date(), ui->DE_DateFinR5->date()) + "--------------------\n";
    }

    if(ui->CB_R6->isChecked()){ // CB6 Activé
        res += "R6 : \n" + this->GetTagDateAllContactBetweenTwoDates(ui->DE_DateDebutR6->date(), ui->DE_DateFinR6->date()) + "--------------------\n";
    }
    ui->PT_ShowResults->setPlainText(QString::fromStdString(res));
}

/**
 * @brief Override de la méthode appelée lors d'une demande de fermeture de la fenêtre
 * @param[out] event     Event de fermeture de la fenêtre
 */
void UI_RequestContact::closeEvent(QCloseEvent *event)
{
    // On joue le son du bouton
    SoundPlayer::PlayButtonSound();

    //event->ignore();  //Empêche la fermeture de la fenêtre
    //event->accept();  //Ré-autorise la fermeture de la fenêtre si ignore() appelé
}

std::string UI_RequestContact::NbContact(){
    return "6\n";
}

std::string UI_RequestContact::GetAllInteractionsBetweenTwoDates(QDate d1, QDate d2){
    return "Titre : Interaction 1\nContenu : Contenu 1\n\nTitre : Interaction 2\nContenu : Contenu 2\n";
}

std::string UI_RequestContact::GetTagTodoContactBetweenTwoDates(int idContact, QDate d1, QDate d2){
    return "Tag 1 : Tag num 1\nTag 2 : Tag num 2\n";
}

std::string UI_RequestContact::GetTagDateContactBetweenTwoDates(int idContact, QDate d1, QDate d2){
    return "Tag 1 : Tag num 1\nTag 2 : Tag num 2\n";
}
std::string UI_RequestContact::GetTagTodoAllContactBetweenTwoDates(QDate d1, QDate d2){
    return "Tag 1 : Tag num 1\nTag 2 : Tag num 2\n";
}

std::string UI_RequestContact::GetTagDateAllContactBetweenTwoDates(QDate d1, QDate d2){
    return "Tag 1 : Tag num 1\nTag 2 : Tag num 2\n";
}

void UI_RequestContact::changementStatusCB(){
    if(ui->CB_R2->isChecked()){ // CB2 Activé
        ui->DE_DateDebutR2->setEnabled(1);
        ui->DE_DateFinR2->setEnabled(1);
    }
    else{ // CB2 Désactivé
        ui->DE_DateDebutR2->setEnabled(0);
        ui->DE_DateFinR2->setEnabled(0);
    }

    if(ui->CB_R3->isChecked()){ // CB3 Activé
        ui->DE_DateDebutR3->setEnabled(1);
        ui->DE_DateFinR3->setEnabled(1);
        ui->L_ContactR3->setEnabled(1);
    }
    else{ // CB3 Désactivé
        ui->DE_DateDebutR3->setEnabled(0);
        ui->DE_DateFinR3->setEnabled(0);
        ui->L_ContactR3->setEnabled(0);
    }

    if(ui->CB_R4->isChecked()){ // CB4 Activé
        ui->DE_DateDebutR4->setEnabled(1);
        ui->DE_DateFinR4->setEnabled(1);
        ui->L_ContactR4->setEnabled(1);
    }
    else{ // CB4 Désactivé
        ui->DE_DateDebutR4->setEnabled(0);
        ui->DE_DateFinR4->setEnabled(0);
        ui->L_ContactR4->setEnabled(0);
    }

    if(ui->CB_R5->isChecked()){ // CB5 Activé
        ui->DE_DateDebutR5->setEnabled(1);
        ui->DE_DateFinR5->setEnabled(1);
    }
    else{ // CB5 Désactivé
        ui->DE_DateDebutR5->setEnabled(0);
        ui->DE_DateFinR5->setEnabled(0);
    }

    if(ui->CB_R6->isChecked()){ // CB6 Activé
        ui->DE_DateDebutR6->setEnabled(1);
        ui->DE_DateFinR6->setEnabled(1);
    }
    else{ // CB6 Désactivé
        ui->DE_DateDebutR6->setEnabled(0);
        ui->DE_DateFinR6->setEnabled(0);
    }

    if(ui->CB_R1->isChecked() || ui->CB_R2->isChecked() || ui->CB_R3->isChecked() || ui->CB_R4->isChecked() || ui->CB_R5->isChecked() || ui->CB_R6->isChecked()){
        ui->B_ExecuterRequete->setEnabled(1);
    }
    else{
        ui->B_ExecuterRequete->setEnabled(0);
    }
}


void UI_RequestContact::getGcFromMainWindow(GestionContact gc){
    this->gc = gc;
    DisplayContactList();
}

/**
 * @brief Méthode pour rafraichir l'affichage de la liste des contacts
 */
void UI_RequestContact::DisplayContactList(){
    ui->L_ContactR3->clear();
    ui->L_ContactR4->clear();
    for(FicheContact c : this->gc.GetAllContacts())
    {
        QString str = QString::fromStdString(c.ToString());
        QListWidgetItem* item = new QListWidgetItem(str);
        QVariant v;
        v.setValue(c.getId());
        item->setData(Qt::UserRole, v);
        ui->L_ContactR3->addItem(QString::fromStdString(c.ToString()), v);
        ui->L_ContactR4->addItem(QString::fromStdString(c.ToString()), v);
    }
}
