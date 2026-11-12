#include "common.h"

void BtlObjAnim_PlayModel(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0 != 0) {
        *(s32 *)(arg0 + 0x37A4) = arg2;
        *(s32 *)(arg0 + 0x37A0) = arg1;
    }
}
