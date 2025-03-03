#include "logging.hpp"

void log(const std::string& msg, bool endl) {
    cout << BOLDCYANN << "[LOG] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}

std::string logS(const std::string& msg, bool endl) {
    return std::string(BOLDCYANN) + "[LOG] " + RESET + msg + (endl ? "\n" : "");
}

void error(const std::string& msg, bool endl) {
    cout << BOLDREDD << "[ERROR] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}

std::string errorS(const std::string& msg, bool endl) {
    return std::string(BOLDREDD) + "[ERROR] " + RESET + msg + (endl ? "\n" : "");
}

void warning(const std::string& msg, bool endl) {
    cout << BOLDYELLOWW << "[WARNING] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}

std::string warningS(const std::string& msg, bool endl) {
    return std::string(BOLDYELLOWW) + "[WARN] " + RESET + msg + (endl ? "\n" : "");
}

void info(const std::string& msg, bool endl) {
    cout << BOLDBLUEE << "[INFO] " << RESET << msg;
    if (endl) cout << std::endl;
    //else cout << '\n';
}

std::string infoS(const std::string& msg, bool endl) {
    return std::string(BOLDBLUEE) + "[INFO] " + RESET + msg + (endl ? "\n" : "");
}

void debug(const std::string& msg, bool endl) {
    cout << BOLDMAGENTAA << "[DEBUG] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}

std::string debugS(const std::string& msg, bool endl) {
    return std::string(BOLDMAGENTAA) + "[DEBUG] " + RESET + msg + (endl ? "\n" : "");
}