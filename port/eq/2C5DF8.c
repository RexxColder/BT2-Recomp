#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002DE618(s32 arg0, s32 arg1, s32 arg2);

void func_002C5DF8(u8 *arg0) {
    s32 out1[4];   /* sp+0: results of the two func_002D07B0 calls, read by func_002DE618 */
    s32 out2[4];
    s32 *temp_s1;
    s32 temp_s2;

    temp_s1 = *(s32 **)(arg0 + 0x1FC0);
    temp_s2 = temp_s1[0];
    out1[0] = func_002D07B0((s32)arg0, 0x5D);
    out1[1] = func_002D07B0((s32)arg0, 0x5E);
    if (out1[0] != 0 && out1[1] != 0 && *(s32 *)((u8 *)temp_s1 + 0x78) == 0xC0) {
        if (func_002DE618(temp_s2, (s32)out1, (s32)out2) == 0) {
            *(s32 *)((u8 *)temp_s1 + 0x78) = 0xC8;
            *(s32 *)((u8 *)temp_s1 + 0x74) = 2;
        }
    }
}
