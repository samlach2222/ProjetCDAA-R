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
