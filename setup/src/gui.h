#ifndef BT2_GUI_H
#define BT2_GUI_H

#include <string>

/* Abre la ventana del setup. Devuelve 0 si se cerró normalmente, 1 si no pudo abrir la ventana. */
int bt2_gui_run(const std::string &root, const std::string &initial_iso, const std::string &initial_dest);

#endif
