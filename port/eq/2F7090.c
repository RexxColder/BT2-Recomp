#include "common.h"

extern u8 D_0037CEA0[] __attribute__((section(".data")));
extern u8 D_0037CED0[] __attribute__((section(".data")));

void func_002EA050(u8 *arg0);
void func_002EA0C8(u8 *arg0, s32 *arg1);
void func_002EA268(s32 arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 func_002ECB18(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *t0, s32 *t1);
void func_002F44A0(u8 *arg0);
void func_002F6838(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002F7090(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 sp10;
    s32 sp14;
    s32 sp18;

    if (arg0 == NULL) {
        func_002EA050(D_0037CEA0);
        return;
    }
    func_002F44A0(arg0);
    if (func_002ECB18(arg1, arg2, *(s32 *)(arg0 + 0xB0), &sp10, &sp14, &sp18) == 0) {
        if (*(s32 *)(arg0 + 8) != 0) {
            *(s32 *)(arg0 + 0xB8) = sp10;
            *(s32 *)(arg0 + 0xB4) = *(s32 *)(arg0 + 0xB0);
            *(s32 *)(arg0 + 0xBC) = sp14;
            *(s32 *)(arg0 + 0xC0) = sp18;
            *(s8 *)(arg0 + 2) = 1;
            *(s8 *)(arg0 + 1) = 1;
            *(s8 *)(arg0 + 0xAC) = 1;
            func_002F6838(arg0, 0, sp14, sp10);
        } else {
            func_002EA268(arg1, arg2, sp, 0x10);
            func_002EA0C8(D_0037CED0, sp);
            *(s16 *)(arg0 + 0x60) = -1;
            *(s8 *)(arg0 + 1) = 6;
        }
    }
}
