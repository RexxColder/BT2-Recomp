#include "common.h"

s32 func_002EC6E8(u8 *arg0);
s64 func_002EC858(u8 *arg0);
void func_002EA050(u8 *arg0);
void func_002F1D30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F1E48(s32 arg0);
s32 func_002F1ED0(s32 arg0);
extern u8 D_0037BD90[] __attribute__((section(".data")));

s32 func_002EB598(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    if (arg1 == 0) {
        func_002EA050(D_0037BD90);
        return -1;
    }
    *(s32 *)(arg0 + 0x3C) = arg1;
    *(s32 *)(arg0 + 0x38) = arg2;
    *(s32 *)(arg0 + 0x18) = 0;
    func_002F1D30(*(s32 *)(arg0 + 4), arg1, arg2, 0, 0xFFFFF);
    if (func_002F1ED0(*(s32 *)(arg0 + 4)) == 4) {
        func_002F1E48(*(s32 *)(arg0 + 4));
        return -1;
    }
    *(s64 *)(arg0 + 0x10) = func_002EC858(arg0);
    temp_v0 = func_002EC6E8(arg0);
    *(s32 *)(arg0 + 0x40) = 0;
    *(s32 *)(arg0 + 0x44) = temp_v0;
    *(s32 *)(arg0 + 0xC) = temp_v0;
    return 0;
}
