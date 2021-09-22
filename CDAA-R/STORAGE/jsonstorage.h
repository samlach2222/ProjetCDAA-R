#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H
#include <string>
#include <LOGIC/gestioncontact.h>

class JSonStorage
{
    private:
        std::string file;
    public:
        JSonStorage(std::string filename);
        void Save(GestionContact gc);
        GestionContact Load();
};

#endif // JSONSTORAGE_H
