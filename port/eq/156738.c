#include "common.h"

void func_00195880(s32 arg0);

void func_00156738(u8 *arg0) {
    u8 *temp_s1;
    s32 *arr;
    s32 k;

    temp_s1 = *(u8 **)(arg0 + 0x38);
    if (*(s32 *)(temp_s1 + 0xAA0) > 0) {
        arr = (s32 *)(temp_s1 + 0xAA4);
        k = 0;
        do {
            if (arr[k] != 0) {
                func_00195880(arr[k]);
            }
            k += 1;
        } while (k < *(s32 *)(temp_s1 + 0xAA0));
    }
}
