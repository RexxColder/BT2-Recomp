#include "common.h"

extern u8 *gBtlStage;

s32 func_00274630(s32 arg0, s32 arg1) {
    u8 *e = (u8 *)*(s32 *)(gBtlStage + 0x5C) + 4 * *(s32 *)(gBtlStage + 0x48) + 80 * arg0;

    if ((*(s32 *)e & 1) != 0) {
        return 0;
    }
    *(s32 *)(e + 8) = *(s32 *)(e + 8) - arg1;
    return *(s32 *)(e + 8) < 1;
}
