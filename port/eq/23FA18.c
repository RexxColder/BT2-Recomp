#include "common.h"

s32 func_001F9758(void *arg0);

s32 func_0023FA18(void *arg0) {
    void *temp_a1;
    s32 temp_s0;
    s32 temp_v0;

    temp_a1 = *(void **)((u8 *)arg0 + 0x1530);
    temp_s0 = *(s32 *)((u8 *)*(void **)((u8 *)temp_a1 + 0x958) + 0x74) / 30;
    temp_v0 = func_001F9758(arg0);
    return temp_s0 + temp_v0 + *(s32 *)((u8 *)arg0 + 0xAEC);
}
