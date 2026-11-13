/* AppImage (package/appimage): el C del juego se compila con los headers de una glibc nueva (C23: strtol y sscanf
 * pasan a __isoc23_*), pero el binario se enlaza contra glibc 2.35 para correr en distros de 2022 en adelante. Con
 * una glibc anterior a 2.38 estos símbolos no existen: se dan acá con la semántica de siempre (la única diferencia
 * de C23 es aceptar el prefijo 0b, que el juego no usa). Con glibc >= 2.38 este archivo queda vacío. */
#include <features.h>
#if !__GLIBC_PREREQ(2, 38)
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

long __isoc23_strtol(const char *s, char **e, int b) { return strtol(s, e, b); }
long long __isoc23_strtoll(const char *s, char **e, int b) { return strtoll(s, e, b); }
unsigned long __isoc23_strtoul(const char *s, char **e, int b) { return strtoul(s, e, b); }
unsigned long long __isoc23_strtoull(const char *s, char **e, int b) { return strtoull(s, e, b); }
int __isoc23_sscanf(const char *s, const char *f, ...) {
    va_list ap;
    int r;
    va_start(ap, f);
    r = vsscanf(s, f, ap);
    va_end(ap);
    return r;
}
#endif
