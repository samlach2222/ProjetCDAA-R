/**
 * @file IHM/ui_filtercontact.h
 * @brief Fichier header pour la fenêtre d'application de filtre sur une recherche de contacts
 * @author Samuel LACHAUD
 */
#ifndef UI_FILTERCONTACT_H
#define UI_FILTERCONTACT_H

#include <QWidget>

namespace Ui {
class UI_FilterContact;
}

/**
 * @brief Classe pour la fenêtre d'application de filtre sur une recherche de contacts
 */
class UI_FilterContact : public QWidget
{
    Q_OBJECT

public:
    explicit UI_FilterContact(QWidget *parent = nullptr);
    ~UI_FilterContact();

private:
    Ui::UI_FilterContact *ui;

public slots:
    void ButtonStartDate();
    void ButtonStopDate();
    void ButtonValidate();
    void ButtonCancel();
};

#endif // UI_FILTERCONTACT_H
