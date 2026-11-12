#include "common.h"

void func_002BCB10(s32 arg0);
void func_002BD1C8(s32 arg0, s32 arg1);
void func_002BD1D8(s32 arg0, s32 arg1);
s32 func_002CCE60(s32 arg0);
void func_002CCF00(s32 arg0);
extern u8 *D_00346C08 __attribute__((section(".data")));

s32 func_002BD088(s32 arg0) {
    s32 temp_s1;
    s32 temp_s2;

    temp_s2 = *(s32 *)((u8 *)arg0 + 0x3C);
    func_002BD1C8(arg0, 1);
    temp_s1 = *(s32 *)((u8 *)arg0 + 0x00);
    if (temp_s1 != 1) {
        func_002BD1C8(arg0, 0);
        return 0;
    }
    D_00346C08 = (u8 *)arg0;
    func_002BD1D8(arg0, 1);
    func_002CCF00(temp_s2);
    func_002BD1D8(arg0, 0);
    if (*(s32 *)((u8 *)arg0 + 0x04) == 0) {
        *(s32 *)((u8 *)arg0 + 0x68) = 0;
    } else {
        *(s32 *)((u8 *)arg0 + 0x68) = temp_s1;
        func_002BCB10(arg0);
    }
    func_002BD1C8(arg0, 0);
    return func_002CCE60(temp_s2) != 1;
}
