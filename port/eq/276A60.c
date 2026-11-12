#include "common.h"

extern u8 *D_003876A0;
extern u8 *gBtlStage;

s32 func_00276A60(u8 *arg0) {
    u8 *stage;
    u8 *t;

    stage = gBtlStage;
    if (stage != NULL && !(*(s64 *)(D_003876A0 + 0x4D8) & 0x2000)) {
        t = *(u8 **)(stage + 4);
        if (t != NULL) {
            *(s32 *)(arg0 + 0) = t[0x1C];
            *(s32 *)(arg0 + 4) = t[0x1D];
            *(s32 *)(arg0 + 8) = t[0x1E];
            return 1;
        }
    }
    *(s32 *)(arg0 + 0xC) = 0x80;
    *(s32 *)(arg0 + 0) = 0x80;
    *(s32 *)(arg0 + 4) = 0x80;
    *(s32 *)(arg0 + 8) = 0x80;
    return 0;
}
