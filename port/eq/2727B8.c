#include "common.h"

void StgOfsTable_Relocate(s32 arg0);
s32 StgOfsTable_Get(s32 arg0, s32 arg1);
s32 func_00271FA8(s32 arg0);
void func_00272680(s32 arg0);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
void Vu1Node_OrFlags(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern u8 *D_00387AB4;

void func_002727B8(void) {
    s32 sp[4];
    u8 *a0;
    u32 x;
    s32 s0;
    s32 s1;
    s32 t;
    s32 g4;
    s32 g5;

    a0 = *(u8 **)(D_003876A0 + 4);
    x = *(u32 *)(a0 + 0x24);
    if (*(u32 *)(a0 + 0x28) != x) {
        s0 = 0;
        D_00387AB4 = a0 + ((x >> 2) * 4);
        StgOfsTable_Relocate((s32)D_00387AB4);
        s1 = func_00271FA8((s32)D_00387AB4);
        if (s1 > 0) {
            do {
                g4 = StgOfsTable_Get((s32)D_00387AB4, s0);
                sp[0] = g4;
                Res_RelocateOffsets((s32)sp, g4, g4);
                t = s0 + 1;
                s0 += 3;
                g5 = StgOfsTable_Get((s32)D_00387AB4, t);
                Vu1Node_OrFlags(g5 + (((*(u32 *)g5) >> 2) * 4), 0x3480, 0x3700);
            } while (s0 < s1);
        }
        func_00272680((s32)D_00387AB4);
        return;
    }
    D_00387AB4 = NULL;
}
