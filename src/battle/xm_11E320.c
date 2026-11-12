#include "m2c_macros.h"

void *memset(void *, int, unsigned int);
s32 BtlStage_FindZoneNear(s32, s32);
void StgCol_InitSphereCtx(void *, s32, s32);
s32 func_0011E130(s32, void *);
void func_00273268(void);
extern s32 D_003876F0;
extern s32 D_003876F4;
extern u8 D_003885A0[] __attribute__((section(".data")));
extern u8 D_003885F0[] __attribute__((section(".data")));

// Resets the stage collision state for zone arg0: clears a 0x50-byte block, finds the zone near arg0, inits the sphere ctx; returns nonzero if D_003885F0 +0xC8 is set.
s32 func_0011E320(s32 arg0, s32 arg1) {
    s32 zone;

    memset(D_003885A0, 0, 0x50);
    func_00273268();
    zone = BtlStage_FindZoneNear(-1, arg0);
    StgCol_InitSphereCtx(D_003885F0, arg0, arg1);
    D_003876F0 = 0;
    D_003876F4 = 0;
    func_0011E130(zone, D_003885F0);
    return D_003885F0[0xC8] != 0;
}
