#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <string>

#ifndef PROCURAR_FILE_H
#define PROCURAR_FILE_H

std::vector<std::string> lista_de_pgns(const char *path);

#endif