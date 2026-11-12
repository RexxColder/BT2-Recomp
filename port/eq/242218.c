#include "common.h"

void StgRigid_Release(s32 arg0);
void func_0025E190(s32 arg0, s32 arg1);
s32 rand(void);
extern u8 *D_003876A0;
extern u8 *D_00387A40;

void func_00242218(u8 *arg0, s32 arg1) {
    s32 temp_v0;
    u32 temp_v1;

    *(s32 *)(arg0 + 0) = 2;
    func_0025E190(*(s32 *)(D_00387A40 + 8) + (*(s32 *)(arg0 + 8) * 0x1520), 0);
    StgRigid_Release(*(s32 *)(arg0 + 0xC));
    temp_v1 = *(u32 *)(arg0 + 0x10);
    if (temp_v1 >= 8U) {
        *(s32 *)(arg0 + 0) = 0;
        temp_v0 = rand();
        *(u32 *)(arg0 + 0x10) = (u32)((temp_v0 - (((s32)((temp_v0 < 0) ? (temp_v0 + 3) : temp_v0) >> 2) * 4)) + 8);
    } else if (arg1 == 0) {
        *(u32 *)(D_003876A0 + 0x4C8) = temp_v1;
    }
}
