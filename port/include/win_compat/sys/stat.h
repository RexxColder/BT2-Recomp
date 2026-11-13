/* Windows (mingw): mkdir recibe sólo la ruta. El port lo llama como en POSIX, mkdir(ruta, modo). */
#pragma once
#include_next <sys/stat.h>
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
