/**
 * @file main.cpp
 * @brief Gère le démarrage de l'application
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 23/09/2021
 */

#include "IHM/mainwindow.h"

#include <QApplication>

/**
 * @brief Gère le lancement de l'application
 * @param[in] argc      Le nombre d'arguments
 * @param[in] argv      Tableau contenant les arguments
 * @return le code de sortie
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
