#include "args.h"
#include "../core/utils/logging.hpp"
#include <cstring>

bool Args::isArg(const std::string& arg) {
    std::string prefixedArg = prefix + arg;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], prefixedArg.c_str()) == 0) {
            return true;
        }
    }
    return false;
}

std::string Args::getArgString(const std::string& arg, std::string DefaultValue) {
    std::string prefixedArg = prefix + arg;
    for (int i = 0; i < argc - 1; i++) { // Ensure there's always an argument following
        if (strcmp(argv[i], prefixedArg.c_str()) == 0) {
            return std::string(argv[i + 1]);
        }
    }
    return DefaultValue;
}


int Args::getArgInt(const std::string& arg,int DefaultValue ) {
    std::string prefixedArg = prefix + arg;
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], prefixedArg.c_str()) == 0) {
            try {
                // Try to convert the next argument to an integer
                return std::stoi(argv[i + 1]);
            } catch (const std::invalid_argument& e) {
                // If it fails, print a warning using the warning function
                warning("The argument '--" + arg + "' expects an integer value, but got a non-integer value: '" + argv[i + 1] + "'. Using default value " + std::to_string(DefaultValue) + " instead.");
            } catch (const std::out_of_range& e) {
                // Handle the case where the number is too large
                warning("The argument '--" + arg + "' has an integer value that is out of range: '" + argv[i + 1] + "'.");
            }
        }
    }
    return DefaultValue;
}