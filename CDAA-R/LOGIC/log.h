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
};

#endif // LOG_H
