#include "common.h"

void func_002E93C0();
void func_002E93D8();
void func_002EA050();
void func_002F4130(s32 arg0, s32 arg1);
void func_002F44A0(s32 arg0);
void func_002F6838(s32 arg0, s32 arg1);
s32 func_00303D48(s32 arg0, s32 arg1);
extern u8 D_0037CF28[] __attribute__((section(".data")));
extern u8 D_0037CF58[] __attribute__((section(".data")));

void func_002F73A8(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    if (arg0 == NULL || arg1 == 0 || arg2 < 0) {
        func_002EA050(D_0037CF28);
        return;
    }
    func_002F44A0((s32)arg0);
    func_002E93C0();
    temp_v0 = func_00303D48(arg1, arg2);
    if (temp_v0 == 0) {
        func_002E93D8(arg0, temp_v0);
        func_002EA050(D_0037CF58);
        return;
    }
    *(u8 *)(arg0 + 2) = 2;
    func_002F4130((s32)arg0, temp_v0);
    func_002F6838((s32)arg0, 0);
    func_002E93D8();
}
