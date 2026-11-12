#include "common.h"

void BattleSetup_Finish(void);
void func_0026E9E8(void *arg0);
void func_0026EA58(void *arg0);
s32 func_0026EB70(void *arg0);
void func_0026EBC0(void *arg0, void *arg1, void *arg2);
void func_0026EC18(void *arg0, void *arg1, s32 arg2);
void func_0026EC48(void *arg0, void *arg1, void *arg2);
void func_0026EEC8(void *arg0, void *arg1, s32 arg2, s32 arg3);
void func_0026EEF8(f32 arg0, void *arg1, void *arg2, s32 arg3);
void func_0026EFC8(void *arg0, void *arg1, s32 arg2);
f32 func_0026F148(void *arg0, void *arg1);
void func_002788A0(s32 arg0, s32 arg1, void *arg2);
void func_0029BD58(s32 arg0);
void func_0029BF08(s32 arg0);
void func_0029C038(void);

extern u8 D_00377818[] __attribute__((section(".data")));
extern u8 D_00377828[] __attribute__((section(".data")));
extern u8 D_00377838[] __attribute__((section(".data")));
extern u8 D_00377858[] __attribute__((section(".data")));
extern u8 D_00377870[] __attribute__((section(".data")));
extern u8 D_00377890[] __attribute__((section(".data")));
extern u8 *D_00387DA0;

void func_0029C1E8(s32 arg0) {
    u8 sp[0x50];
    u8 *s0;
    s32 s1;
    s32 v0;
    s32 v1;
    u8 *a1;

    func_0026E9E8(D_00387DA0 + 8);
    if (*(s32 *)(D_00387DA0 + 0x54) & 8) {
        if (func_0026EB70(D_00387DA0 + 8) & 0x200) {
            *(s32 *)(D_00387DA0 + 0x54) = *(s32 *)(D_00387DA0 + 0x54) | 2;
        }
    }

    if (arg0 != 0) {
        v1 = *(s32 *)(D_00387DA0 + 0x54);
        if (v1 & 4) {
            *(s32 *)(*(u8 **)(D_00387DA0 + 0x50) + 0x34) += 4;
            if (*(s32 *)(*(u8 **)(D_00387DA0 + 0x50) + 0x34) >= 0x61) {
                *(s32 *)(*(u8 **)(D_00387DA0 + 0x50) + 0x34) = 0x60;
            }
        } else if (v1 & 8) {
            *(s32 *)(*(u8 **)(D_00387DA0 + 0x50) + 0x34) -= 4;
            if (*(s32 *)(*(u8 **)(D_00387DA0 + 0x50) + 0x34) < 0) {
                *(s32 *)(*(u8 **)(D_00387DA0 + 0x50) + 0x34) = 0;
            }
        }
        func_002788A0(0, 0, *(u8 **)(D_00387DA0 + 0x50));
    }

    s0 = D_00387DA0 + 8;
    s1 = 0;
    do {
        v0 = s1 << 5;
        *(s32 *)(sp + 0x18) = 0x80;
        *(s32 *)(sp + 0x1C) = v0 + 0x20;
        *(s32 *)(sp + 0x14) = v0;
        *(s32 *)(sp + 0x10) = 0;
        if (s1 != 0) {
            a1 = D_00377818;
        } else {
            a1 = D_00377828;
        }
        func_0026EBC0(s0, a1, sp);
        func_0026EC48(s0, sp, sp + 0x10);
        if (s1 == *(s32 *)(D_00387DA0 + 0x58)) {
            func_0026EBC0(s0, D_00377838, sp + 0x30);
            func_0026EEF8(func_0026F148(s0, sp), s0, sp + 0x30, 0);
        }
        if (*(s32 *)(D_00387DA0 + 0x70) != 0) {
            func_0026EFC8(s0, sp, 4);
        } else {
            func_0026EFC8(s0, sp, 8);
        }
        if (s1 != 0) {
            a1 = D_00377858;
        } else {
            a1 = D_00377870;
        }
        func_0026EBC0(s0, a1, sp);
        if (*(s32 *)(D_00387DA0 + 0x70) != 0) {
            func_0026EFC8(s0, sp, 4);
        } else {
            func_0026EFC8(s0, sp, 8);
        }
        s1 += 1;
    } while (s1 < 2);

    v0 = *(s32 *)(D_00387DA0 + 0x58) << 5;
    *(s32 *)(sp + 0x18) = 0x80;
    *(s32 *)(sp + 0x10) = 0;
    *(s32 *)(sp + 0x14) = v0;
    *(s32 *)(sp + 0x1C) = v0 + 0x20;
    func_0026EBC0(s0, D_00377890, sp);
    func_0026EC48(s0, sp, sp + 0x10);
    func_0026EBC0(s0, D_00377838, sp);
    func_0026EEC8(s0, sp, *(s32 *)(D_00387DA0 + 0x58) * 0x96, 0);
    func_0026EC18(s0, sp, 1);
    if (*(s32 *)(D_00387DA0 + 0x70) != 0) {
        func_0026EFC8(s0, sp, 4);
    } else {
        func_0026EFC8(s0, sp, 8);
    }
    if (*(s32 *)(D_00387DA0 + 0x64) == 1) {
        /* F5: sin titulo en el popup (pedido del usuario: dejar el encabezado vacio) */
        func_0029C038();
    } else {
        func_0029BD58(1);
    }
    func_0026EA58(D_00387DA0 + 8);
    BattleSetup_Finish();
}
