#include "common.h"

void func_0019C2C8(s32 arg0, s32 arg1);

/* 0x002058C0 BtlFx_SpawnClashFlash: if (arg0->0x338 as s64) & (0x8000 << 26) is zero return; otherwise
 * func_0019C2C8(arg0->0x1534, (arg0->0x1530->+4) == 0x28), tail call. */
void BtlFx_SpawnClashFlash(u8 *arg0) {
    s32 a1;

    if ((*(s64 *)(arg0 + 0x338) & ((s64)0x8000 << 26)) == 0) {
        return;
    }
    a1 = (*(s32 *)(*(u8 **)(arg0 + 0x1530) + 0x4) == 0x28) ? 1 : 0;
    func_0019C2C8(*(s32 *)(arg0 + 0x1534), a1);
}
