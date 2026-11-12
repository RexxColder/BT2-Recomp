#include "common.h"

extern u8 *D_003876A0;
extern s32 gBtlStage;

s32 BtlStage_IsReady(void) {
    s32 r = 0;

    if (gBtlStage != 0) {
        r = ((*(s64 *)(D_003876A0 + 0x4D8) & 0x2000) == 0);
    }
    return r;
}
