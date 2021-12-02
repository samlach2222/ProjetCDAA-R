/**
 * @file IHM/ui_requestcontact.cpp
 * @brief Permet de gèrer les requêtes à la base de donnée sur la liste de contacts
 * @author Samuel LACHAUD
 * @version 1.1
 * @date 01/12/2021
 */

#include "ui_requestcontact.h"
#include "ui_ui_requestcontact.h"

#include <LOGIC/soundplayer.h>
#include <STORAGE/databasestorage.h>

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
 */
void UI_RequestContact::ButtonDoRequest()
{
    const bool R1 = ui->CB_R1->isChecked();
    const bool R2 = ui->CB_R2->isChecked();
    const bool R3 = ui->CB_R3->isChecked();
    const bool R4 = ui->CB_R4->isChecked();
    const bool R5 = ui->CB_R5->isChecked();
    const bool R6 = ui->CB_R6->isChecked();
    std::string res = "";
    if(R1){ // CB1 Activé
        res += "R1 :\n" + this->NbContact() + '\n';

        if (R2 || R3 || R4 || R5 || R6){
            res += "------------------------------------------------------------------------------------------\n";
        }
    }

    if(R2){ // CB2 Activé
        res += "R2 :\n" + this->GetAllInteractionsBetweenTwoDates(ui->DE_DateDebutR2->date(), ui->DE_DateFinR2->date()) + '\n';

        if (R3 || R4 || R5 || R6){
            res += "------------------------------------------------------------------------------------------\n";
        }
    }

    if(R3){ // CB3 Activé
        res += "R3 :\n" + this->GetTagTodoContactBetweenTwoDates(ui->L_ContactR3->currentIndex(),ui->DE_DateDebutR3->date(), ui->DE_DateFinR3->date()) + '\n';

        if (R4 || R5 || R6){
            res += "------------------------------------------------------------------------------------------\n";
        }
    }

    if(R4){ // CB4 Activé
        res += "R4 :\n" + this->GetTagDateContactBetweenTwoDates(ui->L_ContactR4->currentIndex(),ui->DE_DateDebutR4->date(), ui->DE_DateFinR4->date()) + '\n';

        if (R5 || R6){
            res += "------------------------------------------------------------------------------------------\n";
        }
    }

    if(R5){ // CB5 Activé
        res += "R5 :\n" + this->GetTagTodoAllContactBetweenTwoDates(ui->DE_DateDebutR5->date(), ui->DE_DateFinR5->date()) + '\n';

        if (R6){
            res += "------------------------------------------------------------------------------------------\n";
        };
    }

    if(R6){ // CB6 Activé
        res += "R6 :\n" + this->GetTagDateAllContactBetweenTwoDates(ui->DE_DateDebutR6->date(), ui->DE_DateFinR6->date());
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

/**
 * @brief Méthode qui sert à obtenir le nombre de contacts de l'application depuis la BDD
 * @return le nombre de contacts de l'application sous forme de chaine de caractères
 */
std::string UI_RequestContact::NbContact(){
    std::string nombreContacts = DatabaseStorage::Request("SELECT COUNT(*) FROM CONTACT")[0].at(0);  //On savait pas quoi choisir entre [] et la fonction at
    std::string resultat = "Il y a "+nombreContacts+" contact";
    if (stoi(nombreContacts) > 1){
        //contacts au pluriel si il y a plus d'un contact
        resultat += 's';
    }
    resultat += " en tout";
    return resultat;
}

/**
 * @brief Méthode qui sert à obtenir la liste de toutes les interactions entre la date \p d1 et la date \p d2
 * @param d1    date de début de la recherche
 * @param d2    date de fin de la recherche
 * @return la liste de toutes les intéractions entre les deux dates sous forme de chaine de caratères
 */
std::string UI_RequestContact::GetAllInteractionsBetweenTwoDates(QDate d1, QDate d2){
    std::string date1 = ConvertQDateIntoSQLiteFormat(d1);
    std::string date2 = ConvertQDateIntoSQLiteFormat(d2, true);

    std::vector<std::vector<std::string>> resultatsRequete = DatabaseStorage::Request("SELECT * FROM INTERACTION WHERE interactionDate BETWEEN '" + date1 + "' AND '" + date2 + "'");

    std::string resultat = "";
    for (std::vector<std::string> ligneResultat : resultatsRequete){
        resultat += ligneResultat[1]+" ("+ligneResultat.at(3)+")\n";
        resultat += ligneResultat[2];

        //Ajoute un saut de ligne si ce n'est pas la dernière interaction
        if (ligneResultat != resultatsRequete.back()){
            resultat += "\n\n";
        }
    }

    //Change le message si resultat est vide
    if (resultat == ""){
        resultat += "Il n'y a aucune interaction créée entre le "+d1.toString("dd/MM/yyyy").toStdString()+" et le "+d2.toString("dd/MM/yyyy").toStdString();
    }

    return resultat;
}

/**
 * @brief Méthode qui sert à obtenir la liste des tags TODO du contact \p idContact entre la date \p d1 et la date \p d2
 * @param idContact identifiant du contact recherché
 * @param d1    date de début de la recherche
 * @param d2    date de fin de la recherche
 * @return la liste de toutes les tags TODO du contact entre les deux dates sous forme de chaine de caratères
 */
std::string UI_RequestContact::GetTagTodoContactBetweenTwoDates(int idContact, QDate d1, QDate d2){
    std::string date1 = ConvertQDateIntoSQLiteFormat(d1);
    std::string date2 = ConvertQDateIntoSQLiteFormat(d2, true);
    std::string contact = std::to_string(idContact);

    std::vector<std::vector<std::string>> resultatsRequete = DatabaseStorage::Request("SELECT tagTodo FROM INTERACTION NATURAL JOIN TAGS WHERE contactId = " + contact + " AND interactionDate BETWEEN '" + date1 + "' AND '" + date2 + "'");

    std::string resultat = "";
    for (std::vector<std::string> ligneResultat : resultatsRequete){
        resultat += ligneResultat.at(0);

        //Ajoute un saut de ligne si ce n'est pas la dernière interaction
        if (ligneResultat != resultatsRequete.back()){
            resultat += '\n';
        }
    }

    //Change le message si resultat est vide
    if (resultat == ""){
        resultat += "Le contact "+ui->L_ContactR3->currentText().toStdString()+" n'a aucune interaction contenant des tags créée entre le "+d1.toString("dd/MM/yyyy").toStdString()+" et le "+d2.toString("dd/MM/yyyy").toStdString();
    }

    return resultat;
}

/**
 * @brief Méthode qui sert à obtenir la liste des tags DATE du contact \p idContact entre la date \p d1 et la date \p d2
 * @param idContact identifiant du contact recherché
 * @param d1    date de début de la recherche
 * @param d2    date de fin de la recherche
 * @return la liste de toutes les tags DATE du contact entre les deux dates sous forme de chaine de caratères
 */
std::string UI_RequestContact::GetTagDateContactBetweenTwoDates(int idContact, QDate d1, QDate d2){
    std::string date1 = ConvertQDateIntoSQLiteFormat(d1);
    std::string date2 = ConvertQDateIntoSQLiteFormat(d2, true);
    std::string contact = std::to_string(idContact);

    std::vector<std::vector<std::string>> resultatsRequete = DatabaseStorage::Request("SELECT tagDate FROM INTERACTION NATURAL JOIN TAGS WHERE contactId = " + contact + " AND interactionDate BETWEEN '" + date1 + "' AND '" + date2 + "'");

    std::string resultat = "";
    for (std::vector<std::string> ligneResultat : resultatsRequete){
        resultat += ligneResultat[0];

        //Ajoute un saut de ligne si ce n'est pas la dernière interaction
        if (ligneResultat != resultatsRequete.back()){
            resultat += '\n';
        }
    }

    //Change le message si resultat est vide
    if (resultat == ""){
        resultat += "Le contact "+ui->L_ContactR4->currentText().toStdString()+" n'a aucune interaction contenant des tags créée entre le "+d1.toString("dd/MM/yyyy").toStdString()+" et le "+d2.toString("dd/MM/yyyy").toStdString();
    }

    return resultat;
}

/**
 * @brief Méthode qui sert à obtenir la liste des tags TODO de tout les contacts entre la date \p d1 et la date \p d2
 * @param d1    date de début de la recherche
 * @param d2    date de fin de la recherche
 * @return la liste de toutes les tags TODO entre les deux dates sous forme de chaine de caratères
 */
std::string UI_RequestContact::GetTagTodoAllContactBetweenTwoDates(QDate d1, QDate d2){
    std::string date1 = ConvertQDateIntoSQLiteFormat(d1);
    std::string date2 = ConvertQDateIntoSQLiteFormat(d2, true);

    std::vector<std::vector<std::string>> resultatsRequete = DatabaseStorage::Request("SELECT tagTodo FROM INTERACTION NATURAL JOIN TAGS WHERE interactionDate BETWEEN '" + date1 + "' AND '" + date2 + "'");

    std::string resultat = "";
    for (std::vector<std::string> ligneResultat : resultatsRequete){
        resultat += ligneResultat.at(0);

        //Ajoute un saut de ligne si ce n'est pas la dernière interaction
        if (ligneResultat != resultatsRequete.back()){
            resultat += '\n';
        }
    }

    //Change le message si resultat est vide
    if (resultat == ""){
        resultat += "Il n'y a aucune interaction contenant des tags créée entre le "+d1.toString("dd/MM/yyyy").toStdString()+" et le "+d2.toString("dd/MM/yyyy").toStdString();
    }

    return resultat;
}

/**
 * @brief Méthode qui sert à obtenir la liste des tags DATE de tout les contacts entre la date \p d1 et la date \p d2
 * @param d1    date de début de la recherche
 * @param d2    date de fin de la recherche
 * @return la liste de toutes les tags DATE entre les deux dates sous forme de chaine de caratères
 */
std::string UI_RequestContact::GetTagDateAllContactBetweenTwoDates(QDate d1, QDate d2){
    std::string date1 = ConvertQDateIntoSQLiteFormat(d1);
    std::string date2 = ConvertQDateIntoSQLiteFormat(d2, true);

    std::vector<std::vector<std::string>> resultatsRequete = DatabaseStorage::Request("SELECT tagDate FROM INTERACTION NATURAL JOIN TAGS WHERE interactionDate BETWEEN '" + date1 + "' AND '" + date2 + "'");

    std::string resultat = "";
    for (std::vector<std::string> ligneResultat : resultatsRequete){
        resultat += ligneResultat[0];

        //Ajoute un saut de ligne si ce n'est pas la dernière interaction
        if (ligneResultat != resultatsRequete.back()){
            resultat += '\n';
        }
    }

    //Change le message si resultat est vide
    if (resultat == ""){
        resultat += "Il n'y a aucune interaction contenant des tags créée entre le "+d1.toString("dd/MM/yyyy").toStdString()+" et le "+d2.toString("dd/MM/yyyy").toStdString();
    }

    return resultat;
}

/**
 * @brief Slot permettant quand on coche/décoche une checkBox d'activer/désactiver les différents controleurs
 */
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

/**
 * @brief Slot permettant d'obtenir la GestionContact envoyée par la MainWindow
 * @param gc    GestionContact
 */
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

/**
 * @brief Convertie un QDate en un string au format SQLite
 * @param[in] date  QDate à convertir au format SQLite
 * @param[in] fin  Si il s'agit d'une date de début (par défaut) ou de fin
 * @return un string au format SQLite
 */
std::string UI_RequestContact::ConvertQDateIntoSQLiteFormat(QDate date, bool fin)
{
    if (fin){
        return date.toString("yyyy-MM-dd 23:59:59").toStdString();
    } else {
        return date.toString("yyyy-MM-dd 00:00:00").toStdString();
    }
}
