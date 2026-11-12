#include "common.h"

s32 BtlStage_IsReady(void);
extern u8 *gBtlStage;
extern u8 D_00387AC0;
extern f32 D_00387AC4;

/* 0x00276478 EftWater_GetSurfaceY(out): when BtlStage_IsReady() and gBtlStage->+4 is set, its byte at +0x15 selects
 * the state: nonzero stores 1 and the float at +0x18 into D_00387AC0 / D_00387AC4, zero stores 0 and 0.0f. Then
 * *out = D_00387AC4 and the result is D_00387AC0 (unsigned byte). */
s32 func_00276478(f32 *arg0) {
    u8 *sub;

    if (BtlStage_IsReady()) {
        sub = (u8 *)*(s32 *)(gBtlStage + 4);
        if (sub != 0) {
            if (sub[0x15] != 0) {
                D_00387AC0 = 1;
                D_00387AC4 = *(f32 *)(sub + 0x18);
            } else {
                D_00387AC0 = 0;
                D_00387AC4 = 0.0f;
            }
        }
    }
    *arg0 = D_00387AC4;
    return D_00387AC0;
}
