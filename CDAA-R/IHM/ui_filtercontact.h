/**
 * @file IHM/ui_filtercontact.h
 * @brief Fichier header pour la fenêtre d'application de filtre sur une recherche de contacts
 * @author Samuel LACHAUD
 */
#ifndef UI_FILTERCONTACT_H
#define UI_FILTERCONTACT_H

#include <QWidget>

#include <QDate>

#include "../LOGIC/fichecontact.h"
#include "../LOGIC/gestioncontact.h"

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
    std::string filtreNom;
    std::string filtreEntreprise;
    QDate filtreDateDebut;
    QDate filtreDateFin;
    bool filtreTriAlphabetique;
    bool filtreTrieDateCreation;
    GestionContact gc;
    bool VerificationChamps();
    void closeEvent(QCloseEvent*);
public slots:
    void ButtonValidate();
    void ReceiveFromMainWindow(GestionContact);

signals:
    /**
     * @brief Envoie la liste des contacts filtrée à a MainWindow
     */
    void sendListContactToMainWindow(std::vector<FicheContact>);
};

#endif // UI_FILTERCONTACT_H
