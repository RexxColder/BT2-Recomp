#include "common.h"

void func_002B24C8(s32 arg0, void *arg1, void *arg2);
void *memset(void *s, int c, unsigned int n);
void func_0025E638(void *arg0, void *arg1);

void func_0025FAF0(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 sp[4];
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s0 = arg0 + 0x3580;
    temp_s1 = arg0 + 0xBD0;
    func_002B24C8(*(s32 *)(arg1 + arg2 * 4 + 0x60), temp_s0, sp);
    *(u8 **)(temp_s1 + 0x28) = temp_s0;
    *(s32 *)(arg0 + 0xD80) = 3;
    if (temp_s0 != NULL) {
        *(s16 *)(temp_s1 + 4) = (s16)arg2;
        *(s32 *)(temp_s1 + 0x14) = 0;
        *(s32 *)(temp_s1 + 0x10) = 0;
        *(f32 *)(temp_s1 + 8) = (f32)*(u16 *)(temp_s0 + 2);
        memset(arg0 + 0xC00, 0, 0x8E);
        func_0025E638(arg0, arg1);
    }
}
