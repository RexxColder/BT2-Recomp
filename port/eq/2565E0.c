#include "common.h"

#define SW32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define SETW32(p, off, v) (*(s32 *)((u8 *)(p) + (off)) = (v))

extern u8 *D_003879E8;
extern u8 D_00376238[] __attribute__((section(".data")));
extern u8 D_00376248[] __attribute__((section(".data")));
extern u8 D_00376258[] __attribute__((section(".data")));
extern u8 D_00376270[] __attribute__((section(".data")));
extern u8 D_00376280[] __attribute__((section(".data")));

void func_00325830();
void func_0026EBC0(void *a0, void *a1, void *a2);
void func_0026EC18(void *a0, void *a1, s32 a2, s32 a3);
void func_0026EC48(void *a0, void *a1, void *a2);
void func_0026EEC8(void *a0, void *a1, s32 a2, s32 a3);
void func_0026EFC8(void *a0, void *a1, s32 a2);
void func_0026EA58(void *a0);
void func_0024A198(void *a0, void *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3);
void func_00250DC0(s32 a0);
void func_002510E0(void);
void BattleSetup_Finish(void);

void func_002565E0(void) {
    u8 fr[0x40];
    u8 sp30[0x40];
    u8 *g;
    u8 *s1;
    u8 *rec;
    s32 i;
    s32 next;
    s32 a3;
    s32 a3b;
    s32 v1;
    s32 var;

    g = D_003879E8;
    if (g != NULL) {
        s1 = g + 4;
        i = 0;
        do {
            next = i + 1;
            func_00325830(sp30, D_00376238, next);
            func_0026EBC0(s1, sp30, fr);
            a3 = 1 << i;
            if (SW32(g, 0x50) == i) {
                func_0026EC18(s1, fr, 1, a3);
            } else if (SW32(g, 0x60) & a3) {
                func_0026EC18(s1, fr, 4, a3);
            } else {
                func_0026EC18(s1, fr, 0, a3);
            }
            a3b = SW32(g + i * 4 + 0x60, 4);
            rec = *(u8 **)(g + 0x58) + ((a3b * 3) * 16);
            v1 = SW32(rec, 8) << 6;
            SETW32(fr, 0x14, 0);
            SETW32(fr, 0x1C, 0x40);
            SETW32(fr, 0x10, v1);
            SETW32(fr, 0x18, v1 + 0x40);
            func_00325830(sp30, D_00376248, next, a3b);
            func_0026EBC0(s1, sp30, fr);
            func_0026EC48(s1, fr, fr + 0x10);
            func_00325830(sp30, D_00376258, next);
            func_0026EBC0(s1, sp30, fr);
            func_0024A198(s1, fr, 2, 0, SW32(g, 0), a3b + 1, 0, 0x160);
            i = next;
        } while (i < 7);
        func_0026EBC0(s1, D_00376270, fr);
        func_0026EEC8(s1, fr, -2, (SW32(g, 0x50) * 0x2D) - 1);
        SETW32(fr, 0x14, 0x20);
        SETW32(fr, 0x18, 0x100);
        SETW32(fr, 0x1C, 0x40);
        SETW32(fr, 0x10, 0);
        func_0026EBC0(s1, D_00376280, fr);
        func_0026EC48(s1, fr, fr + 0x10);
        if (SW32(g, 0x4C) & 8) {
            func_0026EFC8(s1, fr, 4);
        } else {
            func_0026EFC8(s1, fr, 8);
        }
        func_0026EA58(g + 4);
        BattleSetup_Finish();
        if (SW32(g, 0x4C) & 2) {
            func_002510E0();
            if (!(SW32(g, 0x4C) & 8)) {
                var = SW32(g, 0x54);
            } else {
                var = SW32(g, 0x50);
            }
            func_00250DC0(SW32(g + var * 4, 0x64));
            BattleSetup_Finish();
        }
    }
}
