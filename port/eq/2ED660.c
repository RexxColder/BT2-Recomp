#include "common.h"

void func_002EA050(void *arg0, s32 arg1);
void func_002EA0C8(void *arg0, void *arg1);
void func_002EA268(s32 arg0, s32 arg1, void *arg2, s32 arg3);
s32 func_002ECB18(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4, s32 *arg5);
s32 func_002ECD38(s32 arg0, s32 arg1, void *arg2, s32 arg3);
void func_002FFC78(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 D_0037C330[] __attribute__((section(".data")));
extern u8 D_0037C360[] __attribute__((section(".data")));

void func_002ED660(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[8];
    s32 temp_s2;
    s32 temp_v0;

    temp_s2 = *(s32 *)(arg0 + 0x94);
    if (arg0 == NULL) {
        func_002EA050(D_0037C330, arg2);
        return;
    }
    if (func_002ECB18(arg1, arg2, *(s32 *)(arg0 + 0xB0), &sp[4], &sp[5], &sp[6]) == 0) {
        temp_v0 = func_002ECD38(arg1, arg2, sp, 0x10);
        func_002FFC78(temp_s2, temp_v0, sp[4], sp[5], sp[6]);
        return;
    }
    func_002EA268(arg1, arg2, sp, 0x10);
    func_002EA0C8(D_0037C360, sp);
}
