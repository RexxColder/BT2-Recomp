#include "common.h"

extern u8 D_003885A0[] __attribute__((section(".data")));
extern u8 D_003885F0[] __attribute__((section(".data")));
extern s32 D_003876F0;
extern s32 D_003876F4;
extern void func_00273268(void);
extern s32 BtlStage_FindZoneNear(s32 a0, s32 a1);
extern void StgCol_InitSphereCtx(u8 *ctx, s32 a1, s32 a2);
extern void func_0011E130(s32 zone, u8 *ctx);

s32 StgCol_CollectSphere(s32 arg0, s32 arg1) {
    s32 zone;

    __builtin_memset(D_003885A0, 0, 0x50);
    func_00273268();
    zone = BtlStage_FindZoneNear(-1, arg0);
    StgCol_InitSphereCtx(D_003885F0, arg0, arg1);
    D_003876F0 = 0;
    D_003876F4 = 0;
    func_0011E130(zone, D_003885F0);
    return *(u8 *)(D_003885F0 + 0xC8) != 0;
}
