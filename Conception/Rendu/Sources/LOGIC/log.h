/**
 * @file LOGIC/log.h
 * @brief Fichier header pour les logs de l'application
 * @author Samuel LACHAUD
 */
#ifndef LOG_H
#define LOG_H

#include <string>
#include <vector>

/**
 * @brief Classe pour les logs de l'application
 *
 * Cette classe gère l'affichage des différents évenements de l'application. Tout est consigné ici, chaque modifications, ajout ou suppression des divers éléments
 * L'utilisateur pourra donc depuis l'affichage de cette classe dans la MainWindow savoir qu'est-ce qui  a été effectué et quand.
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 */
class Log
{
    private :
        std::vector<std::string> tabLog;
    public:
        const std::vector<std::string> &getTabLog() const;
        void setTabLog(const std::vector<std::string> &newTabLog);

        Log();
        void AddToTabLog(std::string);
};

#endif // LOG_H
