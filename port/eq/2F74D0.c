#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern u8 D_0037CF88[] __attribute__((section(".data")));
extern u8 D_0037CFB8[] __attribute__((section(".data")));

void func_002EA050(void *arg0);
void func_002F44A0(void *arg0, void *arg1, s32 arg2);
void func_002E93C0(void);
void func_002E93D8(void);
s32 func_00303D48(s32 arg0, s32 arg1, s32 arg2);
void func_002F4130(void *arg0, s32 arg1);
void func_002F6838(void *arg0, s32 arg1);

void func_002F74D0(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 v1, x, y, a2, temp_v0;

    if (arg0 == NULL || arg1 == NULL || arg2 < 0) {
        func_002EA050(D_0037CF88);
        return;
    }
    func_002F44A0(arg0, arg1, arg2);
    v1 = W(arg1, 4);
    x = (s32)(((u32)v1 >> 24) | ((u32)v1 << 24) | (((u32)v1 << 8) & 0xFF0000u) | (((u32)v1 >> 8) & 0xFF00u));
    if (!(arg2 < x)) {
        return;
    }
    if (arg2 < 0) {
        return;
    }
    func_002E93C0();
    v1 = W(arg1 + arg2 * 8, 8);
    a2 = (s32)(((u32)v1 >> 8) & 0xFF00u);
    y = (s32)(((u32)v1 >> 24) | ((u32)v1 << 24) | (((u32)v1 << 8) & 0xFF0000u) | (u32)a2);
    temp_v0 = func_00303D48((s32)(arg1 + 0) + y, 0x40000000, a2);
    if (temp_v0 == 0) {
        func_002E93D8();
        func_002EA050(D_0037CFB8);
        return;
    }
    *(u8 *)(arg0 + 2) = 2;
    func_002F4130(arg0, temp_v0);
    func_002F6838(arg0, 0);
    func_002E93D8();
}
