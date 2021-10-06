/**
 * @file LOGIC/tagsIntegration.h
 * @brief Fichier header pour la gestion des tags des intéractions
 * @author Samuel LACHAUD
 */
#ifndef TAGSINTERACTION_H
#define TAGSINTERACTION_H


class tagsInteraction
{
private:
    std::vector<std::tuple<std::string, std::string>> tags;
public:
    tagsInteraction();
    void addTag(std::string, std::string);
    void resetTags();
    std::vector<std::tuple<std::string, std::string>> getTags();
    void setTags(std::vector<std::tuple<std::string, std::string>>);
};

#endif // TAGSINTERACTION_H
