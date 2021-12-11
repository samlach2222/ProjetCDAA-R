/**
 * @file LOGIC/log.cpp
 * @brief Contient les logs de l'application
 * @author Samuel LACHAUD
 * @author Loïs PAZOLA
 * @version 1.0
 * @date 22/09/2021
 */

#include "log.h"

#include "horodatage.h"

#include <STORAGE/databasestorage.h>

/**
 * @brief Retourne la liste de logs
 * @return la liste de logs
 * @author Samuel LACHAUD
 */
const std::vector<std::string> &Log::getTabLog() const
{
    return tabLog;
}

/**
 * @brief Remplace la liste de logs
 * @param[in] newTabLog      La nouvelle liste de logs
 * @author Samuel LACHAUD
 */
void Log::setTabLog(const std::vector<std::string> &newTabLog)
{
    tabLog = newTabLog;
}

/**
 * @brief Constructeur de la classe Log
 * @author Samuel LACHAUD
 */
Log::Log() : tabLog(std::vector<std::string>())
{

}

/**
 * @brief Ajoute un log \p log à la liste de logs
 * @param[in] log       Le log à ajouter
 * @author Samuel LACHAUD
 */
void Log::AddToTabLog(std::string log)
{
    Horodatage h = Horodatage();
    tabLog.push_back('(' + h.ToStringShowLog() + ')' + '\n' + log);
    DatabaseStorage::CreateLog('(' + h.ToStringShowLog() + ')' + '\n' + log);
}

