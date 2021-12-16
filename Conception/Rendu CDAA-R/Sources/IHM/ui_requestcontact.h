/**
 * @file IHM/ui_requestcontact.h
 * @brief Fichier header pour la fenêtre de requêtes sur la base de donnée
 * @author Samuel LACHAUD
 */
#ifndef UI_REQUESTCONTACT_H
#define UI_REQUESTCONTACT_H

#include <QWidget>

#include <LOGIC/gestioncontact.h>

namespace Ui {
class UI_RequestContact;
}

/**
 * @brief Classe pour la fenêtre de requêtes sur la base de donnée
 *
 * Cette classe est ouvert par l'appui d'un bouton sur la MainWindow. Ell permet d'effectuer des requêtes sur la base de données.
 * Ces différentes requêtes permettent d'avoir des appercus avancés de l'ensemble des contacts et de leurs composants.
 * C'est par exemple ici que l'on pourra récupérer les différents tags des différents contacts.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
class UI_RequestContact : public QWidget
{
    Q_OBJECT

public:
    explicit UI_RequestContact(QWidget *parent = nullptr);
    ~UI_RequestContact();

private:
    GestionContact gc;
    Ui::UI_RequestContact *ui;
    void closeEvent(QCloseEvent*);
    std::string NbContact();
    std::string GetAllInteractionsBetweenTwoDates(QDate d1, QDate d2);
    std::string GetTagTodoContactBetweenTwoDates(int idContact, QDate d1, QDate d2);
    std::string GetTagDateContactBetweenTwoDates(int idContact, QDate d1, QDate d2);
    std::string GetTagTodoAllContactBetweenTwoDates(QDate d1, QDate d2);
    std::string GetTagDateAllContactBetweenTwoDates(QDate d1, QDate d2);
    void DisplayContactList();
    std::string ConvertQDateIntoSQLiteFormat(QDate, bool = false);

public slots:
    void ButtonDoRequest();
    void changementStatusCB();
    void getGcFromMainWindow(GestionContact);
};

#endif // UI_REQUESTCONTACT_H
