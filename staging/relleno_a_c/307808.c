#include "common.h"

extern s32 D_003A00E0[] __attribute__((section(".data")));
extern s32 D_00366468[] __attribute__((section(".data")));
extern s32 D_00366488[] __attribute__((section(".data")));

/* 0x00307808: despacha el grupo arg0 de D_003A00E0: para cada uno de los 6 huecos con fn != 0:
 * D_00366488[arg0] = 1 (en curso), r = fn(arg), D_00366488[arg0] = 0, acumula r con OR. Después
 * D_00366468[arg0]++ (contador de pasadas). Devuelve el OR. Índice sin comprobar, como el original. */
s32 func_00307808(s32 arg0) {
    s32 *slot = D_003A00E0 + arg0 * 18;
    s32 acc = 0;
    s32 i;

    for (i = 0; i < 6; i++, slot += 3) {
        if (slot[0] != 0) {
            D_00366488[arg0] = 1;
            acc |= ((s32 (*)(s32))slot[0])(slot[1]);
            D_00366488[arg0] = 0;
        }
    }
    D_00366468[arg0] += 1;
    return acc;
}
