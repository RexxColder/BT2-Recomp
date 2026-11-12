#include "common.h"

void func_002EBA98(void *arg0, s32 arg1);
s8 func_002F1ED0(s32 arg0);
s32 func_002F1F78(s32 arg0);

void func_002EC388(u8 *arg0) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    s8 temp_s1;
    s8 temp_v0_2;

    if (*(s8 *)(arg0 + 1) == 2) {
        *(s8 *)(arg0 + 1) = func_002F1ED0(*(s32 *)(arg0 + 4));
        temp_a1 = *(s32 *)(arg0 + 0x18);
        temp_v0 = func_002F1F78(*(s32 *)(arg0 + 4)) - temp_a1;
        temp_a1_2 = temp_a1 + temp_v0;
        *(s32 *)(arg0 + 0x24) = temp_v0;
        if ((u32)((u8)*(s8 *)(arg0 + 1) - 3) < 2U) {
            *(s32 *)(arg0 + 0x18) = temp_a1_2;
            func_002EBA98(arg0, temp_a1_2);
        }
    }
    temp_s1 = *(s8 *)(arg0 + 3);
    if (temp_s1 == 1) {
        temp_v0_2 = func_002F1ED0(*(s32 *)(arg0 + 4));
        if (temp_v0_2 == temp_s1) {
            *(s32 *)(arg0 + 0x24) = func_002F1F78(*(s32 *)(arg0 + 4)) - *(s32 *)(arg0 + 0x18);
            ((void (*)(void *))func_002EBA98)(arg0);
            *(s8 *)(arg0 + 1) = temp_v0_2;
            *(s8 *)(arg0 + 3) = 0;
        }
    }
}
