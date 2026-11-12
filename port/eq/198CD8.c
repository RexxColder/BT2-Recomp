#include "common.h"

void EftGlow_SpawnNext(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void EftGlow_Emit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_v1;
    s32 n;
    s32 i;

    temp_v1 = *(s32 *)(arg0 + 0x30);
    if (temp_v1 < 0x41) {
        n = 0xE;
        if (temp_v1 + 0xE >= 0x42) {
            n = 0x41 - temp_v1;
        }
        for (i = 0; i < n; i++) {
            EftGlow_SpawnNext(arg0, arg1, arg2, arg3, arg4, arg5);
        }
    }
}
