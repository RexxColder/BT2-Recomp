#include "common.h"

extern u8 D_3B0B00 __attribute__((section(".data")));
extern u8 *D_00421C08 __attribute__((section(".data")));

void func_003BC460(void);
void func_003BC568(void);
void func_2711A0(void);
void func_2711E8(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);
void func_278A40(s32 arg0, u8 *arg1);
s32 func_28C4B8(s32 arg0);

/* 0x003BC5A8: unless (D_3B0B00+0x104 == 1 and func_28C4B8(0) == 0), func_003BC460() and then a loop: call
 * func_2711A0, func_28B090, func_28BDA0, func_297978; if (D_3B0B00+0x104 != 1 or func_28C4B8(0) != 0) clear the
 * word at G->0xC->0x24 and call func_278A40(G->8, G->0xC) (G = D_00421C08); func_2711E8; repeat while the same
 * condition holds (the test is D_3B0B00+0x104 != 1 or func_28C4B8(0) != 0). Then func_003BC568, func_28B218.
 * Returns 1. */
s32 func_003BC5A8(void) {
    u8 *g;

    if (*(s32 *)((u8 *)&D_3B0B00 + 0x104) == 1 && func_28C4B8(0) == 0) {
        return 1;
    }

    func_003BC460();
    do {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        if (*(s32 *)((u8 *)&D_3B0B00 + 0x104) != 1 || func_28C4B8(0) != 0) {
            g = D_00421C08;
            *(s32 *)(*(u8 **)(g + 0xC) + 0x24) = 0;
            func_278A40(*(s32 *)(g + 8), *(u8 **)(g + 0xC));
        }
        func_2711E8();
    } while (*(s32 *)((u8 *)&D_3B0B00 + 0x104) != 1 || func_28C4B8(0) != 0);

    func_003BC568();
    func_28B218();
    return 1;
}
