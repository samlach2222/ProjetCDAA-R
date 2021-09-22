#include "log.h"
#include "horodatage.h"
#include <vector>
#include <string>

std::vector<std::string> Log::getTabLog()
{
    return tabLog;
}

Log::Log()
{
    tabLog = std::vector<std::string>();
}

void Log::AddToTabLog(std::string log)
{
    Horodatage h = Horodatage();
    tabLog.push_back("( " + h.ToString() + " ) " + log);
}

