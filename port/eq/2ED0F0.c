#include "common.h"

s32 func_002ED0F0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = (s32) ((arg0 < 0) ? (arg0 + 0x7FF) : arg0) >> 0xB;
    return temp_v0 + ((arg0 - (temp_v0 << 0xB)) > 0);
}
