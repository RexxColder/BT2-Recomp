#include "common.h"

extern s32 BtlPad_Test4C();

void func_002182A8(u8 *obj) {
    if (BtlPad_Test4C(obj, 3)) {
        *(s32 *)(obj + 0x9C0) = 3;
    }
    if (BtlPad_Test4C(obj, 2)) {
        *(s32 *)(obj + 0x9C0) = 2;
    }
    if (BtlPad_Test4C(obj, 1)) {
        *(s32 *)(obj + 0x9C0) = 1;
    }
    if (BtlPad_Test4C(obj, 0)) {
        *(s32 *)(obj + 0x9C0) = 0;
    }
}
