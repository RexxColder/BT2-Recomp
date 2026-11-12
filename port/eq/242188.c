#include "common.h"

s32 StgRigid_Release(s32 arg0);
s32 func_0025E190(s32 arg0, s32 arg1);
s32 rand(void);
extern u8 *D_00387A40;

void func_00242188(u8 *arg0) {
    s32 v0;
    s32 x;

    *(s32 *)(arg0 + 0) = 3;
    func_0025E190(*(s32 *)(D_00387A40 + 8) + *(s32 *)(arg0 + 8) * 0x1520, 0);
    StgRigid_Release(*(s32 *)(arg0 + 0xC));
    if (*(u32 *)(arg0 + 0x10) >= 8U) {
        *(s32 *)(arg0 + 0) = 0;
        v0 = rand();
        x = (v0 < 0) ? v0 + 3 : v0;
        *(u32 *)(arg0 + 0x10) = (u32)((v0 - ((x >> 2) << 2)) + 8);
    }
}
