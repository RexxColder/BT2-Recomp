#include "common.h"

s32 BtlTask_SetDead(s32 arg0);
void func_001A1EC0(s32 arg0);
s32 func_001A21C8(s32 arg0);
extern u8 *D_003876A0;

void func_001A1998(u8 *arg0) {
    s32 s0;

    s0 = *(s32 *)(arg0 + 0x38);
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        func_001A1EC0(s0);
        if (func_001A21C8(s0) == 0) {
            BtlTask_SetDead((s32)arg0);
        }
    }
}
