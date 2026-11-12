#include "common.h"

extern u8 func_00183228[] __attribute__((section(".data")));

void func_00182B60(s32 arg0, s16 arg1) {
    u8 *vt;
    u8 *temp_v1;

    if (arg0 == 0) {
        return;
    }
    vt = (u8 *)*(s32 *)((u8 *)arg0 + 0x28);
    if (*(s32 *)vt != (s32)0x00183228u) {
        return;
    }
    if (*(u8 *)((u8 *)arg0 + 0) & 1) {
        return;
    }
    temp_v1 = (u8 *)*(s32 *)((u8 *)arg0 + 0x38);
    *(s16 *)(temp_v1 + 0xAD2) = arg1;
    *(u16 *)(temp_v1 + 0xAD6) = *(u16 *)(temp_v1 + 0xAD6) | 0x40;
}
