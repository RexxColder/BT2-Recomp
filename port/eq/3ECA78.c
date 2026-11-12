#include "m2c_macros.h"

extern void *D_00428F4C __attribute__((section(".data")));

void func_003ECA78(s32 arg0) {
    u8 *p;
    u8 *q;
    s32 v;

    if (arg0 == 0) {
        p = (u8 *)D_00428F4C;
        q = M2C_FIELD(p, u8 **, 0xCC);
        v = M2C_FIELD(q, s32 *, 0x10);
        M2C_FIELD(p, s32 *, 0x148) = v;
        M2C_FIELD(p, s32 *, 0x150) = v;
        M2C_FIELD(p, s32 *, 0x14C) = v;
        M2C_FIELD(p, s32 *, 0x160) = 0;
        M2C_FIELD(p, s32 *, 0x164) = 0;
    } else if (arg0 == 1) {
        p = (u8 *)D_00428F4C;
        q = M2C_FIELD(p, u8 **, 0xD0);
        v = M2C_FIELD(q, s32 *, 0x10);
        M2C_FIELD(p, s32 *, 0x148) = v;
        M2C_FIELD(p, s32 *, 0x160) = v;
        M2C_FIELD(p, s32 *, 0x164) = v;
        M2C_FIELD(p, s32 *, 0x150) = 0;
        M2C_FIELD(p, s32 *, 0x14C) = 0;
    }
}
