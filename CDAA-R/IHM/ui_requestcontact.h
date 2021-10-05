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

class UI_RequestContact : public QWidget
{
    Q_OBJECT

public:
    explicit UI_RequestContact(QWidget *parent = nullptr);
    ~UI_RequestContact();

private:
    Ui::UI_RequestContact *ui;

public slots:
    void ButtonDoRequest();
    void ButtonCancel();
};

#endif // UI_REQUESTCONTACT_H
