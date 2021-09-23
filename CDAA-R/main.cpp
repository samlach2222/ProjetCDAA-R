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
 * @param argc
 * @param argv
 * @return Retourne le lancement de l'application
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
