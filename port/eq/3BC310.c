#include "common.h"

extern s32 D_00421388 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 D_00421C88[] __attribute__((section(".data")));

void func_24BE18(void);
void func_003BC5A8(void);
void func_003BBD98(void);
s32 func_100D58(u8 *arg0, s32 arg1, s32 arg2);
void func_100950(s32 arg0);
void func_003BC000(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s64 arg5);
void func_24BA78(u8 *arg0);
void func_100990(s32 arg0);
void func_28BB60(void *arg0);
s32 func_24BE80(void);
int Port_SkipIntro(void);   /* F4: port/full/plat_intro.c */

/* 0x003BC310: the init sequence: func_24BE18(); func_003BC5A8(); func_24BE18(); func_003BBD98(); if D_00421388 == 0:
 * func_100D58(*(D_003876A4+4)+7, 0, 1) then D_00421388 = func_100D58(0,0,0) until nonzero. Then the func_003BC000
 * calls (5,0x3C,1,1,1,0), (4,0x3C,1,1,1,0), (2,0x3C,1,0,0,1), (3,0x3C,1,0,0,0), (1,0x3C,0,0,1,0) with func_24BE18
 * between, func_24BA78(&D_00421C88), func_100990(1), func_28BB60(D_00421388), func_24BE18(); tail-calls func_24BE80(). */
s32 func_003BC310(void) {
    func_24BE18();
    func_003BC5A8();
    func_24BE18();
    func_003BBD98();
    /* F4: pad y memory card ya inicializados; saltear logos + LOGO_O + opening. */
    if (Port_SkipIntro()) {
        /* F4: el tramo salteado tambien inicializa el sonido: D_00387F20[1] = 1 y carga la particion AFS 1. */
        func_100950(1);
        func_100990(1);
        func_24BE18();
        return 0;
    }
    if (D_00421388 == 0) {
        func_100D58(*(u8 **)(D_003876A4 + 4) + 7, 0, 1);
        do {
            D_00421388 = func_100D58(0, 0, 0);
        } while (D_00421388 == 0);
    }
    func_100950(1);
    func_24BE18();
    func_003BC000(5, 0x3C, 1, 1, 1, 0);
    func_24BE18();
    func_003BC000(4, 0x3C, 1, 1, 1, 0);
    func_24BE18();
    func_24BA78(D_00421C88);
    func_24BE18();
    func_003BC000(2, 0x3C, 1, 0, 0, 1);
    func_003BC000(3, 0x3C, 1, 0, 0, 0);
    func_003BC000(1, 0x3C, 0, 0, 1, 0);
    func_100990(1);
    func_28BB60((void *)(s32)D_00421388);
    func_24BE18();
    return func_24BE80();
}
