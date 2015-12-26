#ifndef GETVAR_H
#define GETVAR_H

#include <string>

int GetVarInt(std::string File, std::string Section, std::string Entry);
std::string GetVar(std::string File, std::string Section, std::string Entry);
void SetVar(std::string File, std::string Section, std::string Entry, std::string Value);
void SetVarInt(std::string File, std::string Section, std::string Entry, int Value);

#endif
