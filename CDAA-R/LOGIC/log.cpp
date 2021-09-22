#include "log.h"
#include "horodatage.h"
#include <vector>
#include <string>

Log::Log()
{
    tabLog = std::vector<std::string>();
}

void Log::AddToTabLog(std::string log)
{
    Horodatage h = Horodatage();
    tabLog.push_back("( " + h.ToString() + " ) " + log);
}

