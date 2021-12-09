/**
 * @file LOGIC/tagsInteraction.h
 * @brief Fichier header pour la gestion des tags des interactions
 * @author Samuel LACHAUD
 */
#ifndef TAGSINTERACTION_H
#define TAGSINTERACTION_H

#include <string>
#include <tuple>
#include <vector>

/**
 * @brief Classe gérant le tableau des tags
 */
class tagsInteraction
{
private:
    std::vector<std::tuple<std::string, std::string>> tags;
public:
    const std::vector<std::tuple<std::string, std::string> > &getTags() const;
    void setTags(const std::vector<std::tuple<std::string, std::string> > &newTags);

    tagsInteraction();
    void addTag(std::string, std::string);
};

#endif // TAGSINTERACTION_H
