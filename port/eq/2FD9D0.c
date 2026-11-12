#include "common.h"

s32 func_002FB550(void *arg0, s32 arg1, s32 arg2);
void func_002FB5D8(s32 arg0);
s32 func_002FB678(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4);
void func_002FB9F0(s32 arg0);
void func_002FC0B0(void);
void func_002FC1D8(void);
void func_002FD2E8(u8 *arg0);
void func_0032F698(s32 arg0, s32 arg1, u8 *arg2, s32 arg3);
s32 sceCdSync(s32 arg0);
extern u8 D_00356D00[] __attribute__((section(".data")));
extern s32 D_00356D04 __attribute__((section(".data")));
extern u8 D_0037E428[] __attribute__((section(".data")));
extern u8 D_0037E440[] __attribute__((section(".data")));
extern u8 D_0037E460[] __attribute__((section(".data")));

s32 func_002FD9D0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_s1;
    s32 temp_v1;
    s32 v;

    if (arg0 == NULL) {
        func_002FD2E8(D_0037E428);
        return 0;
    }
    if (arg1 < 0) {
        func_002FD2E8(D_0037E440);
        return 0;
    }
    if (arg2 == 0) {
        func_002FD2E8(D_0037E460);
        return 0;
    }
    if (*(s8 *)(arg0 + 2) == 2) {
        return 0;
    }
    if (arg1 == 0) {
        *(s8 *)(arg0 + 2) = 1;
        return 0;
    }
    v = func_002FB550(arg0, arg1, arg2);
    *(s32 *)(arg0 + 0x1C) = v;
    if (v == 0) {
        return 0;
    }
    temp_v1 = *(s32 *)(arg0 + 8) - *(s32 *)(arg0 + 0xC);
    arg0[0x44] = D_00356D00[0];
    temp_a3 = (arg1 >= temp_v1) ? temp_v1 : arg1;
    arg0[0x45] = D_00356D00[1];
    *(s32 *)(arg0 + 0x10) = temp_a3;
    arg0[0x46] = D_00356D00[2];
    *(s32 *)(arg0 + 0x18) = arg2;
    func_0032F698(arg2, (arg2 + (temp_a3 << 11)) - 1, D_00356D00, temp_a3);
    if (func_002FB678(*(s32 *)(arg0 + 0x1C), *(s32 *)(arg0 + 0x20) + *(s32 *)(arg0 + 0xC),
                      *(s32 *)(arg0 + 0x10), *(s32 *)(arg0 + 0x18), arg0 + 0x44) != 0) {
        temp_s1 = D_00356D04;
        if (temp_s1 != 1) {
            *(s8 *)(arg0 + 2) = 2;
        } else {
            sceCdSync(0);
            func_002FC1D8();
            func_002FC0B0();
            func_002FB9F0(*(s32 *)(arg0 + 0x1C));
            func_002FB5D8(*(s32 *)(arg0 + 0x1C));
            *(s32 *)(arg0 + 0x1C) = 0;
            *(s32 *)(arg0 + 0x14) = arg1;
            *(s8 *)(arg0 + 2) = (s8)temp_s1;
            *(s32 *)(arg0 + 0xC) = *(s32 *)(arg0 + 0xC) + *(s32 *)(arg0 + 0x10);
        }
        return *(s32 *)(arg0 + 0x10);
    }
    func_002FB5D8(*(s32 *)(arg0 + 0x1C));
    return 0;
}
