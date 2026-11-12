#include "common.h"

void func_00104E90(void);
void func_00260F80(void);
void func_0025CBC8(s32 arg0);
void func_00265BC8(void);
void func_00265D40(s32 arg0, s32 arg1, f32 farg0);
void func_00265EB8(s32 arg0);
void func_0025CC68(void);
s32 func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 D_003B0B00[] __attribute__((section(".data")));

s32 func_00105000(void) {
    s32 temp_v1;

    func_00104E90();
    func_00260F80();
    func_0025CBC8(0);
    func_00265BC8();
    func_00265D40(0, -1, 0.0f);
    func_00265EB8(0);
    temp_v1 = *(s32 *)(D_003B0B00 + 0x134);
    if (temp_v1 & 1) {
        func_0025CC68();
        temp_v1 = *(s32 *)(D_003B0B00 + 0x134);
    }
    if (temp_v1 & 0x3000) {
        func_00297FE0(0, 2, 0x40, 0x40, 1);
        return 1;
    }
    return 0;
}
