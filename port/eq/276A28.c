#include "common.h"

extern u8 *D_003876A0;
extern u8 *gBtlStage;

s32 func_00276A28(void) {
    s32 v = 0;
    s32 x;

    if (gBtlStage != NULL && !(*(s32 *)(D_003876A0 + 0x4D8) & 0x2000)) {
        x = *(s32 *)(gBtlStage + 4);
        v = (x == 0) ? 0 : x + 0xA70;
    }
    return v;
}
