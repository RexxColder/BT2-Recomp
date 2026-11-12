#include "common.h"

char *strncpy(char *d, const char *s, u32 n);
extern s32 D_003A0370[2] __attribute__((section(".data")));
extern char D_003664A8[] __attribute__((section(".data")));

/* 0x003070D0: reporte de error del cliente IOP al callback D_003A0370 = {fn, arg} (lo fija func_00307798).
 * msg NULL: fn(arg, 0) SIN comprobar fn (como el original). Si no: copia hasta 0x7F caracteres a D_003664A8
 * (strncpy, sin forzar el 0 final) y, si fn != 0, fn(arg, D_003664A8). */
void func_003070D0(const char *msg) {
    if (msg == NULL) {
        ((void (*)(s32, char *))D_003A0370[0])(D_003A0370[1], NULL);
        return;
    }
    strncpy(D_003664A8, msg, 0x7F);
    if (D_003A0370[0] != 0) {
        ((void (*)(s32, char *))D_003A0370[0])(D_003A0370[1], D_003664A8);
    }
}
