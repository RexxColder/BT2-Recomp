#include "common.h"

s32 strcmp(s32 arg0, s32 arg1);
void func_002EFAB8(s32 arg0, s32 arg1);
s32 func_002FE6C8(s32 arg0, s32 arg1);
void func_002FE708(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002FE5D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_0037E580[] __attribute__((section(".data")));
extern u8 D_0037E588[] __attribute__((section(".data")));
extern u8 D_00356CF0[] __attribute__((section(".data")));

s32 func_002FE7C8(s32 arg0, u8 *arg1) {
    s32 sp[2];

    if (strcmp((s32)D_0037E580, arg0) == 0) {
        *(s32 *)(arg1 + 4) = -1;
        *(s32 *)(arg1 + 0) = 0;
        func_002EFAB8((s32)D_0037E588, 0x2E);
        return 1;
    }
    if (func_002FE6C8(arg0, 0x2E) == 1) {
        func_002FE708(arg0, (s32)&sp[0], (s32)&sp[1], 1);
        *(s32 *)(arg1 + 4) = (s32)((u32)sp[1] << 11);
        *(s32 *)(arg1 + 0) = sp[0];
        return 0;
    }
    *(s32 *)(arg1 + 0) = 0;
    *(s32 *)(arg1 + 4) = 0;
    if (*(s32 *)(D_00356CF0 + 0) != 0) {
        func_002FE5D8((s32)arg1, arg0, *(s32 *)(D_00356CF0 + 0), *(s32 *)(D_00356CF0 + 4));
    }
    return 0;
}
