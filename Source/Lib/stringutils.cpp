#include <string>
#include "Lib/stringutils.h"
#include <sstream>
#include <vector>


using namespace std;

bool StartsWith(string String, string Prefix)
{
	return String.substr(0, Prefix.size()) == Prefix;
}


std::vector<std::string> &Split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    Split(s, delim, elems);
    return elems;
}
