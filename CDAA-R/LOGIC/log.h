/**
 * @file LOGIC/log.h
 * @brief Fichier header pour les logs de l'application
 * @author Samuel LACHAUD
 */
#ifndef LOG_H
#define LOG_H

#include <vector>
#include <string>

/**
 * @brief Classe pour les logs de l'application
 */
class Log
{
    private :
        std::vector<std::string> tabLog;
    public:
        Log();
        void AddToTabLog(std::string log);
        std::vector<std::string> getTabLog();
        void SetTabLog(std::vector<std::string> logs);
};

#endif // LOG_H
