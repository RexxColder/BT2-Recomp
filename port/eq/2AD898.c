#include "common.h"

s32 func_0020C870(s32 arg0);
s32 func_0020C8A0(s32 arg0);
s32 func_0020C8E8(void);
s32 func_00284E08(s32 arg0);
s32 func_00284E68(s32 arg0, s32 arg1, f32 farg0);
void func_002ACE58(s32 arg0);
s32 func_002ACF10(s32 arg0);
s32 func_002AD340(s32 arg0);
extern u8 D_003B2654[] __attribute__((section(".data")));

s32 func_002AD898(void) {
    u8 *g;
    s32 state;
    s32 t;

    g = D_003B2654;
    state = *(s32 *)(g + 0x50);
    if (state == 1) {
        if (func_00284E08(0) != 0) {
            *(s32 *)(g + 0x50) = 2;
        }
        return 0;
    }
    if (state < 2) {
        if (state != 0) {
            return 0;
        }
        if (func_002ACF10(0) != 0) {
            func_00284E68(0, 0, 1.0f);
            *(s32 *)(g + 0x50) = 1;
            return 0;
        }
        if (*(s32 *)g < 0) {
            if (func_0020C8A0(0) == 0) {
                return 0;
            }
            *(u8 *)(g + 0x3BC) = 1;
            *(u8 *)(g + 0x18) = 1;
            func_002ACE58(*(s32 *)(g + 0x64));
            *(s32 *)(g + 0x44) = -1;
            func_00284E68(0, 0, 1.0f);
            *(s32 *)(g + 0x50) = 1;
            return 0;
        }
        if (func_0020C870(0) == 0) {
            return 0;
        }
        *(u8 *)(g + 0x3BC) = 1;
        t = func_0020C8E8();
        *(s32 *)(g + 0x44) = t;
        *(s32 *)(g + 0x4C) = t;
        t = func_002AD340(t);
        *(u8 *)(g + 0x18) = 1;
        func_002ACE58(t);
        func_00284E68(0, 0, 1.0f);
        *(s32 *)(g + 0x50) = 1;
        return 0;
    }
    if (state == 2) {
        return 1;
    }
    return 0;
}
