/**
 * @file LOGIC/log.h
 * @brief Fichier header pour les logs de l'application
 * @author Samuel LACHAUD
 */
#ifndef LOG_H
#define LOG_H
#include <vector>
#include <string>

class Log
{
    private :
        std::vector<std::string> tabLog;
    public:
        Log();
        void AddToTabLog(std::string log);
        std::vector<std::string> getTabLog();
};

#endif // LOG_H
