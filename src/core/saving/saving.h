#ifndef SAVING_H
#define SAVING_H

#include <string>
#include <filesystem>
#include <fstream>
#include "../utils/logging.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

//TODO: Rewrite this entire thing

class Saving
{
private:
    std::string path;
    json saveData;

public:
    Saving(std::string path);
    ~Saving();

    void checkSaveFile();
    void loadSaveFile();
    void saveSaveFile();

    void saveUniqueId(const std::string& server, int id);
    int getUniqueId(const std::string& server);
};

#endif
