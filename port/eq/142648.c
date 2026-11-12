#include "common.h"

s32 BtlPool_Alloc(s32 arg0, s32 arg1);
void BtlPool_Free(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent();
void EftStorm_InitRain();
void EftStorm_Reset(s32 arg0);
s32 EftTexSet_Load32(s32 arg0, s32 arg1);
void func_00143790(void);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_003876A0;
extern s32 gEftStorm;

void func_00142648(s32 arg0) {
    u8 *s0;
    s32 temp;

    if (*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 47)) {
        s0 = *(u8 **)(D_003876A0 + 4) + 0x40;
    } else {
        s0 = *(u8 **)(D_003876A0 + 4);
    }
    if (gEftStorm != 0) {
        BtlPool_Free(BtlPool_GetCurrent(arg0), gEftStorm);
        gEftStorm = 0;
    }
    temp = BtlPool_Alloc(BtlPool_GetCurrent(), 0x8EF0);
    gEftStorm = temp;
    memset((void *)temp, 0, 0x8EF0);
    EftTexSet_Load32(gEftStorm, (s32)(s0 + ((*(u32 *)(s0 + 0x38) >> 2) << 2)));
    EftStorm_Reset(arg0);
    EftStorm_InitRain();
    func_00143790();
}
