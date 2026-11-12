#include "common.h"

extern u8 *gEftShotFx;

s32 func_00126560(void);
u8 *func_001B5698(void);

s32 func_001B56D8(s32 arg0, s32 arg1) {
    s32 mode = arg1 & 0xFF;
    u8 *v1;

    if (func_00126560() != 0) {
        v1 = func_001B5698();
        if (v1 == NULL) {
            return 0;
        }
    } else {
        v1 = *(u8 **)gEftShotFx + arg0 * 0x10;
    }
    if (mode == 1) {
        *(s32 *)(v1 + 0) = arg0;
        *(s32 *)(v1 + 8) = 0;
        *(s32 *)(v1 + 0xC) = *(s32 *)(v1 + 0xC) | 0x12;
    } else if (mode == 0) {
        *(s32 *)(v1 + 0) = arg0;
        *(s32 *)(v1 + 4) = 0;
        *(s32 *)(v1 + 0xC) = *(s32 *)(v1 + 0xC) | 0x21;
    } else if (mode == 2) {
        *(s32 *)(v1 + 0) = arg0;
        *(s32 *)(v1 + 0xC) = 0;
    }
    return 1;
}
