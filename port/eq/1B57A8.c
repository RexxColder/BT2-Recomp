#include "common.h"

s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
s32 EftTexSet_Load32(s32 arg0, s32 arg1);
s32 func_00126460(s32 arg0);
void *memset(void *s, s32 c, u32 n);
extern u8 *gEftShotFx;

s32 func_001B57A8(void) {
    s32 s0v;
    s32 r;

    if (gEftShotFx == NULL) {
        gEftShotFx = (u8 *)BtlPool_Alloc(BtlPool_GetCurrent(), 0x60);
        memset(gEftShotFx, 0, 0x60);
    }
    if (*(s32 *)(gEftShotFx + 0x00) == 0) {
        *(s32 *)(gEftShotFx + 0x00) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x50);
        memset((void *)*(s32 *)(gEftShotFx + 0x00), 0, 0x50);
    }
    if (*(s32 *)(gEftShotFx + 0x04) == 0) {
        *(s32 *)(gEftShotFx + 0x04) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x12C0);
        memset((void *)*(s32 *)(gEftShotFx + 0x04), 0, 0x12C0);
    }
    if (*(s32 *)(gEftShotFx + 0x50) == 0) {
        *(s32 *)(gEftShotFx + 0x50) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x208);
        memset((void *)*(s32 *)(gEftShotFx + 0x50), 0, 0x208);
    }
    s0v = *(s32 *)(gEftShotFx + 0x50);
    r = func_00126460(0x1D);
    return EftTexSet_Load32(s0v, r);
}
