#include "common.h"

void *memset(void *dst, s32 c, u32 n);
void func_002EFAB8(void *fmt, s32 arg1, s32 arg2);
u32 sceSifAllocIopHeap(u32 size);
s32 func_00306560(s32 arg0, s32 arg1, s32 arg2);
s32 func_00305510(s32 arg0, s32 arg1, s32 arg2);
s32 func_00306CB8(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_0035D220 __attribute__((section(".data")));
extern s32 D_0035D224 __attribute__((section(".data")));
extern s32 D_0035D228 __attribute__((section(".data")));
extern s32 D_0035D22C __attribute__((section(".data")));
extern s32 D_0035D230 __attribute__((section(".data")));
extern s8 D_0035D234 __attribute__((section(".data")));
extern u8 D_0035D280[] __attribute__((section(".data")));
extern u8 D_0035D580[] __attribute__((section(".data")));
extern u8 D_0037F0A8[] __attribute__((section(".data")));
extern u8 D_0037F0F0[] __attribute__((section(".data")));
extern u8 D_0037F120[] __attribute__((section(".data")));
extern u8 D_0037F150[] __attribute__((section(".data")));
extern u8 D_0037F188[] __attribute__((section(".data")));
extern u8 D_0037F1B8[] __attribute__((section(".data")));
extern u8 D_0037F1F0[] __attribute__((section(".data")));

/* 0x00301A98: crea los canales de voz en el IOP.
 * Si D_0035D228 == 0: D_0035D220 = 16 canales, D_0035D224 = 0x41000 bytes.
 * Si D_0035D22C == 0: reserva D_0035D224 + 0x40 en el heap del IOP (falla -> printf y cuelga), printf de
 * control (D_0037F0F0, tamaño, dirección), D_0035D234 = 1, D_0035D230 = (dir + 0x40) & ~0x3F.
 * Limpia D_0035D280 (16 x 0x18 bytes = 0x300) y, para cada canal i < D_0035D220, con p = D_0035D230 que avanza:
 *   e = D_0035D280 + i*0x18; e+0 = 0; p debe estar alineado a 64 (si no: printf y cuelga);
 *   e+4 = func_00306560(1, p, 0x100) (0 -> cuelga); p += 0x100 (alineado o cuelga);
 *   e+8 = func_00305510(1, D_0035D580 + i*0x100, 0x100) (objeto con vtabla; 0 -> cuelga);
 *   e+0x10 = p, e+0x14 = 0x4000, vtabla[+0x20](obj, 0, e+0x10); p += 0x4000;
 *   e+0xC = func_00306CB8(obj, e+4, 1) (0 -> cuelga).
 * Los "cuelga" son bucles infinitos tras el printf, como en el original. */
void func_00301A98(void) {
    u8 *e;
    s32 p;
    s32 i;
    s32 obj;

    if (D_0035D228 == 0) {
        D_0035D220 = 0x10;
        D_0035D224 = 0x41000;
    }
    if (D_0035D22C == 0) {
        D_0035D22C = (s32)sceSifAllocIopHeap(D_0035D224 + 0x40);
        if (D_0035D22C == 0) {
            func_002EFAB8(D_0037F0A8, D_0035D224 + 0x40, 0);
            for (;;) {
            }
        }
        func_002EFAB8(D_0037F0F0, D_0035D224 + 0x40, D_0035D22C);
        D_0035D234 = 1;
        D_0035D230 = (D_0035D22C + 0x40) & ~0x3F;
    }
    memset(D_0035D280, 0, 0x300);
    p = D_0035D230;
    for (i = 0; i < D_0035D220; i++) {
        e = D_0035D280 + i * 0x18;
        *(s8 *)(e + 0) = 0;
        if (p & 0x3F) {
            func_002EFAB8(D_0037F120, 0, 0);
            for (;;) {
            }
        }
        *(s32 *)(e + 4) = func_00306560(1, p, 0x100);
        p += 0x100;
        if (*(s32 *)(e + 4) == 0) {
            func_002EFAB8(D_0037F150, 0, 0);
            for (;;) {
            }
        }
        if (p & 0x3F) {
            func_002EFAB8(D_0037F188, 0, 0);
            for (;;) {
            }
        }
        *(s32 *)(e + 8) = func_00305510(1, (s32)(D_0035D580 + i * 0x100), 0x100);
        if (*(s32 *)(e + 8) == 0) {
            func_002EFAB8(D_0037F1B8, 0, 0);
            for (;;) {
            }
        }
        obj = *(s32 *)(e + 8);
        *(s32 *)(e + 0x14) = 0x4000;
        *(s32 *)(e + 0x10) = p;
        ((void (*)(s32, s32, u8 *))(*(s32 *)(*(s32 *)obj + 0x20)))(obj, 0, e + 0x10);
        p += 0x4000;
        *(s32 *)(e + 0xC) = func_00306CB8(*(s32 *)(e + 8), *(s32 *)(e + 4), 1);
        if (*(s32 *)(e + 0xC) == 0) {
            func_002EFAB8(D_0037F1F0, 0, 0);
            for (;;) {
            }
        }
    }
}
