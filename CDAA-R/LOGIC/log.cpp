/**
 * @file LOGIC/log.cpp
 * @brief Contient les logs de l'application
 * @author Samuel LACHAUD
 * @version 1.0
 * @date 22/09/2021
 */
#include "log.h"
#include "horodatage.h"
#include <vector>
#include <string>

/**
 * @brief Constructeur de la classe Log
 */
Log::Log()
{
    tabLog = std::vector<std::string>();
}

/**
 * @brief Retourne la liste de logs
 * @return la liste de logs
 */
std::vector<std::string> Log::getTabLog()
{
    return tabLog;
}

/**
 * @brief Ajoute un log \p log à la liste de logs
 * @param[in] log       Le log à ajouter
 */
void Log::AddToTabLog(std::string log)
{
    Horodatage h = Horodatage();
    tabLog.push_back("( " + h.ToString() + " ) "+ "\n" + log);
}

