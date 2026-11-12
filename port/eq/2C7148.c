#include "common.h"

void func_002C07B0(u8 *a0, s32 a1, s32 a2);

void func_002C7148(u8 *arg0, s32 arg1) {
    func_002C07B0(arg0, *(s32 *)(arg0 + 0x1FC8), arg1);
    *(s64 *)(arg0 + 0x9A8) = (s64)arg1 + *(s64 *)(arg0 + 0x9A8);
}
