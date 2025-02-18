#include "logging.hpp"

void log(const string& msg, bool endl) {
    cout << BOLDCYANN << "[LOG] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}

void error(const string& msg, bool endl) {
    cout << BOLDREDD << "[ERROR] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}

void warning(const string& msg, bool endl) {
    cout << BOLDYELLOWW << "[WARNING] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}

void info(const string& msg, bool endl) {
    cout << BOLDBLUEE << "[INFO] " << RESET << msg;
    if (endl) cout << std::endl;
    //else cout << '\n';
}

void debug(const string& msg, bool endl) {
    cout << BOLDMAGENTAA << "[DEBUG] " << RESET << msg;
    if (endl) cout << std::endl;
    else cout << '\n';
}