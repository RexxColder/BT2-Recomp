#include "common.h"

void Rand_Range(void *arg0, void *arg1);
s32 func_002B64F0(void *arg0);
void func_002C5A78(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_00377F18[];
extern u8 D_00377F50[];

void func_002B3C80(void *arg0) {
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    u8 *temp_a1;

    temp_a1 = *(u8 **)((u8 *)arg0 + 0x178);
    if (temp_a1 != NULL) {
        temp_s3 = *(s32 *)(temp_a1 + 8);
        temp_s2 = *(s32 *)((u8 *)arg0 + 0x18) + 4;
        temp_s1 = *(s32 *)(temp_a1 + 0);
        if (*(s32 *)(temp_a1 + 4) < (temp_s2 * temp_s3)) {
            Rand_Range(D_00377F50, temp_a1);
            return;
        }
        if (func_002B64F0(arg0) != 1) {
            return;
        }
        func_002C5A78(*(s32 *)((u8 *)arg0 + 0x3C), temp_s1, temp_s2, temp_s3);
        return;
    }
    Rand_Range(D_00377F18, temp_a1);
}
