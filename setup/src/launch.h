/* Lanzar el binario del juego desde el setup, sin bloquear la ventana. */
#ifndef BT2_LAUNCH_H
#define BT2_LAUNCH_H

#include <stddef.h>

/* Busca el binario: BT2_GAME, port/build/full/bt2full, ../BT2-test/bin/bt2.
 * Devuelve 1 y copia la ruta en `out` si existe y es ejecutable; 0 si no. */
int bt2_find_game(const char *root, char *out, size_t outsz);

/* Lanza el juego en segundo plano desde `root`, con BT2_DATA/BT2_ELF apuntando a `dest`.
 * Devuelve 0 si arrancó; -1 con `err` cargado si no. */
int bt2_launch_game(const char *root, const char *dest, char *err, size_t errsz);

#endif /* BT2_LAUNCH_H */
