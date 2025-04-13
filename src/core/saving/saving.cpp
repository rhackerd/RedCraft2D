#include "saving.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

Saving::Saving(std::string path)
{
    #ifdef _WIN32
    this->path = std::string(std::getenv("APPDATA")) + "/redcraft/saves/";
    #elif __linux__
    this->path = std::string(std::getenv("HOME")) + "/.local/share/redcraft/saves/";
    #else
    this->path = "saves/";
    error("Couldn't recognize the operating system, using default path (./saves/)");
    #endif

    this->checkSaveFile();
    this->loadSaveFile();
}

void Saving::checkSaveFile()
{
    fs::path savePath = this->path;
    if (!fs::exists(savePath)) {
        if (fs::create_directories(savePath)) {
            info("Created save directory: " + this->path);
        } else {
            error("Failed to create save directory: " + this->path);
        }
    }
}

void Saving::loadSaveFile()
{
    std::ifstream saveFile(this->path + "save.json");
    if (!saveFile.is_open()) {
        info("Failed to open save file, creating a new one.");
        this->saveSaveFile();
        return;
    }
    saveFile >> saveData;
    saveFile.close();

    // Ensure "IDS" exists
    if (!saveData.contains("IDS") || !saveData["IDS"].is_object()) {
        saveData["IDS"] = json::object();
    }
}

void Saving::saveSaveFile()
{
    std::ofstream saveFile(this->path + "save.json");
    if (!saveFile.is_open()) {
        error("Failed to save game data.");
        return;
    }

    saveFile << saveData.dump(4);
    saveFile.close();
}

void Saving::saveUniqueId(const std::string& server, int id)
{
    saveData["IDS"][server] = id;
    saveSaveFile();
}

int Saving::getUniqueId(const std::string& server)
{
    if (!saveData.contains("IDS") || !saveData["IDS"].contains(server)) {
        info("No ID found for " + server + ", initializing with 0.");
        saveData["IDS"][server] = 0;
        saveSaveFile();
    }
    return saveData["IDS"][server];
}

Saving::~Saving() {}
