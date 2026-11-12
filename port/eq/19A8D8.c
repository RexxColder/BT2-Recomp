#include "common.h"

void EftGlow_SetType(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 *gEftGlow;

void EftGlow_ChangeType(s32 arg0, s32 arg1, s32 arg2) {
    u8 *entry;

    if (arg0 >= 2) {
        return;
    }
    if (gEftGlow == NULL || arg1 < 0) {
        return;
    }
    entry = *(u8 **)(*(u8 **)(gEftGlow + 0x6F0) + arg0 * 4);
    if (entry != NULL) {
        EftGlow_SetType(*(s32 *)(entry + 0x38), arg0, arg1, arg2);
    }
}
