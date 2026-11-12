#include "common.h"

void Res_RelocateOffsets(void *arg0, void *arg1, void *arg2);
void *memset(void *dst, s32 c, u32 n);
extern void *D_003876A0;
extern u8 gGfxLens[] __attribute__((section(".data")));

void func_00283880(void) {
    u8 *temp_v1;
    u8 *temp_v1_2;

    memset(gGfxLens, 0, 0x190);
    temp_v1 = *(u8 **)((u8 *)D_003876A0 + 0x7C);
    temp_v1_2 = temp_v1 + ((*(u32 *)(temp_v1 + 0x180) >> 2) << 2);
    *(u8 **)(gGfxLens + 0x180) = temp_v1_2;
    Res_RelocateOffsets(gGfxLens + 0x180, temp_v1_2, temp_v1_2);
}
