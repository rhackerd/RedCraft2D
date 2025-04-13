#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define BLACKK   "\033[30m"      /* Black */
#define REDD    "\033[31m"      /* Red */
#define GREENN   "\033[32m"      /* Green */
#define YELLOWW  "\033[33m"      /* Yellow */
#define BLUEE    "\033[34m"      /* Blue */
#define MAGENTAA "\033[35m"      /* Magenta */
#define CYANN    "\033[36m"      /* Cyan */
#define WHITEE   "\033[37m"      /* White */
#define BOLDBLACKK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDREDD     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREENN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOWW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUEE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTAA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYANN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITEE   "\033[1m\033[37m"      /* Bold White */

using namespace std;

void log(const string& msg, bool endl = true);
void error(const string& msg, bool endl = true);
void warning(const string& msg, bool endl = true);
void info(const string& msg, bool endl = true);
void debug(const string& msg, bool endl = true);

std::string logS(const string& msg, bool endl = true);
std::string errorS(const string& msg, bool endl = true);
std::string warningS(const string& msg, bool endl = true);
std::string infoS(const string& msg, bool endl = true);
std::string debugS(const string& msg, bool endl = true);

#endif