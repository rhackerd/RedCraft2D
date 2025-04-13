#ifndef ARGS_H
#define ARGS_H

#include <string>
#include <vector>

class Args
{
private:
    int argc;
    char** argv;
    std::string prefix; // Default "--" prefix

public:
    Args(int argc, char** argv) : argc(argc), argv(argv), prefix("--") {}

    bool isArg(const std::string&);
    std::string getArgString(const std::string&, std::string DefaultValue);
    int getArgInt(const std::string&, int DefaultValue);
    std::vector<std::string> getArgs(); // You can implement this if needed
};

#endif
