#include "common.h"
s32 func_002C0EA8(s32 arg0, s32 arg1);

s32 func_002CEDA0(u8 *arg0) {
    return func_002C0EA8((s32)arg0, *(s32 *)(arg0 + 0x1F44)) != 0;
}
