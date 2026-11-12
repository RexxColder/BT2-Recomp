#include "common.h"

void func_002F9300(s32 arg0, s32 arg1, s32 arg2);
u8 *func_002F95C8(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037DCD8[] __attribute__((section(".data")));
extern u8 D_0037DD00[] __attribute__((section(".data")));
extern u8 D_0037DD28[] __attribute__((section(".data")));

void func_002FB048(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[8]; /* asm locals 0x00..0x1F; memset below clears 0x14 bytes (was sp[4]: 4-byte overflow) */
    s32 (*temp_v0_2)(s32, s32, s32, s32);
    u8 *temp_v0;

    if (arg0 == 0) {
        func_002F9300((s32)D_0037DCD8, arg1, arg2);
        return;
    }
    if (arg1 == 0) {
        func_002F9300((s32)D_0037DD00, arg1, arg2);
        return;
    }
    temp_v0 = func_002F95C8(arg0, arg1, arg2);
    if (temp_v0 == 0) {
        func_002F9300((s32)D_0037DD28, 0, 0x14);
        return;
    }
    memset(sp, 0, 0x14);
    sp[1] = arg1;
    temp_v0_2 = (s32 (*)(s32, s32, s32, s32))(*(s32 *)(temp_v0 + 0x60));
    if (temp_v0_2 != 0) {
        temp_v0_2((s32)sp, 6, 0, 0);
    }
}
