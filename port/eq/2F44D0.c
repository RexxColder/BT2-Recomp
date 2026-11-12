#include "common.h"

void func_002EA050(s32 arg0);
void func_002F0480(s32 arg0);
void func_002F1DD8(s32 arg0);
void func_002F4400(s32 arg0);
void func_002FFF90(s32 arg0);
extern void (*D_00354EE0)(s32) __attribute__((section(".data")));
extern u8 D_0037C7B8[] __attribute__((section(".data")));

void func_002F44D0(s32 arg0) {
    s32 temp_a0;
    u8 *temp_v0;
    s32 vt;
    void (*fn)(s32);

    if (arg0 == 0) {
        func_002EA050((s32)D_0037C7B8);
        return;
    }
    if (D_00354EE0 != 0) {
        func_002F0480(*(s32 *)((u8 *)arg0 + 4));
        D_00354EE0(arg0);
    }
    temp_a0 = *(s32 *)((u8 *)arg0 + 8);
    if (temp_a0 != 0) {
        func_002F1DD8(temp_a0);
    }
    if (*(s8 *)((u8 *)arg0 + 2) == 4) {
        func_002FFF90(*(s32 *)((u8 *)arg0 + 0x94));
        temp_v0 = *(u8 **)((u8 *)arg0 + 0x14);
        if (temp_v0 != 0) {
            vt = *(s32 *)temp_v0;
            fn = (void (*)(s32))(*(s32 *)((u8 *)vt + 0x14));
            fn((s32)temp_v0);
        }
    }
    func_002F4400(arg0);
}
