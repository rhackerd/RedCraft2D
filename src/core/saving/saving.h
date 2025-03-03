#ifndef SAVING_H
#define SAVING_H

#include <string>
#include "nlohmann/json.hpp"
#include <filesystem>
#include <fstream>
#include "../utils/logging.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

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
