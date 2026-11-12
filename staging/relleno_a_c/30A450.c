#include "common.h"

void *memset(void *dst, s32 c, u32 n);
extern s32 D_00366A50 __attribute__((section(".data")));
extern u8 D_00366A58[] __attribute__((section(".data")));
extern u8 D_00366ED8[] __attribute__((section(".data")));
extern s32 D_003672D8 __attribute__((section(".data")));
extern u8 D_003672E0[] __attribute__((section(".data")));
extern u8 D_003673E0[] __attribute__((section(".data")));
extern s32 D_00367400 __attribute__((section(".data")));
extern s32 D_00367404 __attribute__((section(".data")));
extern s32 D_00367408 __attribute__((section(".data")));
extern s32 D_0036740C __attribute__((section(".data")));
extern s32 D_00367410 __attribute__((section(".data")));
extern u8 *D_003A0390 __attribute__((section(".data")));
extern u8 D_0037FD70[] __attribute__((section(".data")));

/* 0x0030A450: Init con contador (D_00366A50). Siempre D_003A0390 = &D_0037FD70 (antes de mirar el contador).
 * La primera vez: limpia D_00366A58 (0x480), D_00366ED8 (0x400), D_003673E0 (0x20), llena D_003672E0 (0x100)
 * con 0xFF; D_0036740C = -1, D_00367410 = 1, D_00367400 = D_003672D8 = D_00367404 = D_00367408 = 0. */
void func_0030A450(void) {
    D_003A0390 = D_0037FD70;
    if (D_00366A50 == 0) {
        memset(D_00366A58, 0, 0x480);
        memset(D_00366ED8, 0, 0x400);
        memset(D_003672E0, 0xFF, 0x100);
        memset(D_003673E0, 0, 0x20);
        D_0036740C = -1;
        D_00367410 = 1;
        D_00367400 = 0;
        D_003672D8 = 0;
        D_00367404 = 0;
        D_00367408 = 0;
    }
    D_00366A50 += 1;
}
