/**
 * @file IHM/ui_requestcontact.h
 * @brief Fichier header pour la fenêtre de requêtes sur la base de donnée
 * @author Samuel LACHAUD
 */
#ifndef UI_REQUESTCONTACT_H
#define UI_REQUESTCONTACT_H

#include <QWidget>

namespace Ui {
class UI_RequestContact;
}

/**
 * @brief Classe pour la fenêtre de requêtes sur la base de donnée
 */
class UI_RequestContact : public QWidget
{
    Q_OBJECT

public:
    explicit UI_RequestContact(QWidget *parent = nullptr);
    ~UI_RequestContact();

private:
    Ui::UI_RequestContact *ui;
    void closeEvent(QCloseEvent*);

public slots:
    void ButtonDoRequest();
};

#endif // UI_REQUESTCONTACT_H
