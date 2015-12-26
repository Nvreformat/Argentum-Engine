#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>

bool StartsWith(std::string String, std::string Prefix);
std::vector<std::string> &Split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> Split(const std::string &s, char delim);

#endif
