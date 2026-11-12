#ifndef BT2_PATHS_H
#define BT2_PATHS_H

#include <string>

/* Carpeta del ejecutable, con barra final. */
std::string bt2_exe_dir();
/* Raíz del repo: BT2_SETUP_ROOT, o la carpeta que contiene setup/install.py subiendo desde el ejecutable. */
std::string bt2_root();
/* Ruta absoluta y normalizada (aunque no exista todavía). */
std::string bt2_absolute(const std::string &path);

#endif
