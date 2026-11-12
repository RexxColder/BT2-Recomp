#include "m2c_macros.h"

void func_001833C0(void *arg0) {
    u8 *a = (u8 *)arg0;
    u8 *temp;

    temp = *(u8 **)(a + 0x38);
    if (*(s32 *)(a + 4) & 0x3F) {
        *(f32 *)(temp + 0xA70) = *(f32 *)(a + 0x10);
        *(f32 *)(temp + 0xA74) = *(f32 *)(a + 0x14);
        *(u16 *)(temp + 0xAD6) = (u16)((*(u16 *)(temp + 0xAD6) | 0x400) & 0xFEFF);
        *(f32 *)(temp + 0xA78) = *(f32 *)(a + 0x18);
        *(s32 *)(temp + 0xA48) = 0;
    }
}
