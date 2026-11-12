#include "common.h"

void func_0026E9E8(u8 *arg0);
void func_0026EA58(u8 *arg0);
s32 func_0026EBC0(u8 *arg0, s32 *arg1, s32 *arg2);
void func_0026EC78(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, s32 *arg4, s32 arg5, s32 arg6, s32 arg7);
extern u8 *D_00387988;
extern s32 D_00387990 __attribute__((section(".data")));

void func_0024C060(void) {
    u8 *s0;
    s32 blk[8];

    func_0026E9E8(D_00387988 + 4);
    s0 = D_00387988 + 4;
    blk[6] = 0x200;
    blk[7] = 0x28;
    blk[4] = 0;
    blk[5] = 0;
    func_0026EBC0(s0, &D_00387990, blk);
    func_0026EC78(s0, blk, (s32)(D_00387988 + 0x4C), (s32)(D_00387988 + 0x50), blk + 4, 1, 6, 4);
    func_0026EA58(D_00387988 + 4);
}
