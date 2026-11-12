#include "common.h"

s64 EftVram_AddTex(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387798;

void func_001806F0(s32 arg0) {
    s32 i;
    s32 temp_v1;
    s32 temp_a0;

    if (*(s32 *)(*(s32 *)(arg0 + 0x24) + 4) != 0) {
        i = 0;
        do {
            temp_v1 = *(s32 *)(D_00387798 + i * 4);
            if (temp_v1 != 0) {
                s64 r = EftVram_AddTex(temp_v1, 1, 0);
                temp_a0 = *(s32 *)(D_00387798 + i * 4);
                *(s64 *)temp_a0 = r;
            }
            i++;
        } while (i < 3);
    }
}
