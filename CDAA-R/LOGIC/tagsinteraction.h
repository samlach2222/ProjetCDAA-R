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
    std::vector<std::tuple<std::string, QDate>> tags;
public:
    tagsInteraction();
    std::vector<std::tuple<std::string, QDate>> getTags();
    void setTags(std::vector<std::tuple<std::string, QDate>>);
};

#endif // TAGSINTERACTION_H
