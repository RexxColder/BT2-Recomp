#include "common.h"

u8 *BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void EftTexSet_Load32(u8 *arg0, s32 arg1);
s32 func_00126460(s32 arg0);
s32 func_00126580(void);
void func_00197108(void);
void *memset(void *arg0, s32 arg1, s32 arg2);
extern s32 D_003877E4;
extern u8 *gEftGlow;
extern s32 gEftGlowCfg;
extern s32 gEftGlowCfg2;

void func_0019A3F0(s32 arg0) {
    s32 s0;
    s32 s1;

    s0 = 1;
    s1 = 0;
    gEftGlow = BtlPool_Alloc(BtlPool_GetCurrent(), 0x700);
    memset(gEftGlow, 0, 0x700);
    *(s32 *)gEftGlow = func_00126580();
    *(s32 *)(gEftGlow + 4) = *(s32 *)gEftGlow * 0x46;
    *(s32 *)(gEftGlow + 0xC) = 0;
    *(s32 *)(gEftGlow + 0x10) = 0;
    *(s32 *)(gEftGlow + 0x14) = 0;
    *(u8 **)(gEftGlow + 8) = BtlPool_Alloc(BtlPool_GetCurrent(), *(s32 *)(gEftGlow + 4) * 0xC0);
    memset(*(u8 **)(gEftGlow + 8), 0, *(s32 *)(gEftGlow + 4) * 0xC0);
    *(u8 **)(gEftGlow + 0x6F0) = BtlPool_Alloc(BtlPool_GetCurrent(), *(s32 *)gEftGlow * 4);
    memset(*(u8 **)(gEftGlow + 0x6F0), 0, *(s32 *)gEftGlow * 4);
    *(s32 *)(gEftGlow + 0x2B8) = func_00126460(4);
    *(s32 *)(gEftGlow + 0x4E0) = func_00126460(5);
    do {
        s0 -= 1;
        EftTexSet_Load32(gEftGlow + s1 + 0x2C0, *(s32 *)(gEftGlow + s1 + 0x2B8));
        s1 += 0x228;
    } while (s0 >= 0);

    s0 = 0;
    *(s32 *)(gEftGlow + 0x6F4) = func_00126460(9);
    gEftGlowCfg2 = *(s32 *)(gEftGlow + 0x6F4);
    gEftGlowCfg = gEftGlowCfg2;
    if (*(s32 *)gEftGlow > 0) {
        do {
            *(s32 *)(*(u8 **)(gEftGlow + 0x6F0) + s0 * 4) = 0;
            s0 += 1;
        } while (s0 < *(s32 *)gEftGlow);
    }
    func_00197108();
    D_003877E4 = BtlTask_CreateChildList(arg0, *(s32 *)gEftGlow, 0x2E0);
}
