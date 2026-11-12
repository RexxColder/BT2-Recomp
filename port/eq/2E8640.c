#include "common.h"

void func_002E8640(s32 arg0) {
    s32 fp;
    s32 temp_a1;
    s32 a1;
    s32 a2;

    fp = *(s32 *)((u8 *)arg0 + 0xFC);
    temp_a1 = *(s32 *)((u8 *)arg0 + 0x94) - *(s32 *)((u8 *)arg0 + 0xF4);
    a1 = (temp_a1 < 0) ? (temp_a1 + 0x7FFFFFFF) : temp_a1;
    a2 = *(s32 *)((u8 *)arg0 + 0x90) * (s32)*(s8 *)((u8 *)arg0 + 0xE) * 2;
    ((void (*)(s32, s32, s32, s32))fp)(*(s32 *)((u8 *)arg0 + 0x100), a1, a2, fp);
    *(s32 *)((u8 *)arg0 + 0xF4) = *(s32 *)((u8 *)arg0 + 0x94);
}
