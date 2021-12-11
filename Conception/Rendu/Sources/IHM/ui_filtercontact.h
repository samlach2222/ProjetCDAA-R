/**
 * @file IHM/ui_filtercontact.h
 * @brief Fichier header pour la fenêtre d'application de filtre sur une recherche de contacts
 * @author Samuel LACHAUD
 */
#ifndef UI_FILTERCONTACT_H
#define UI_FILTERCONTACT_H

#include <QWidget>

#include <QDate>

#include <LOGIC/fichecontact.h>
#include <LOGIC/gestioncontact.h>

namespace Ui {
class UI_FilterContact;
}

/**
 * @brief Classe pour la fenêtre d'application de filtre sur une recherche de contacts
 *
 * Cette classe est ouverte par la Mainwindow par appuis sur un bouton. Elle permet alors de filtrer la liste de contacts de cette fenêtre.
 * Les filtres sont appliqués entre deux dates sur des contacts par noms ou par entreprise. Les filtres s'exécutent en local, hors de la base de donnée.
 * @author Samuel LACHAUD
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
    void PrepareSendingToMainWindow(GestionContact);

signals:
    /**
     * @brief Envoie la liste des contacts filtrée à a MainWindow
     *
     * Ce signal permet d'envoyer une nouvelle liste de contacts à la MainWindow.
     * Cette liste de contacts est filtré par cette fenêtre et remplace temporairement la liste de contacts originale afin de la montrer à l'utilisateur
     * @author Samuel LACHAUD
     */
    void sendListContactToMainWindow(std::vector<FicheContact>);
};

#endif // UI_FILTERCONTACT_H
