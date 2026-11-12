#include "common.h"

void func_002EFAB8(void *arg0);
void func_002FBB20(s32 arg0);
void func_002FC0B0(void);
void func_002FD2E8(void *arg0, void *arg1);
void func_002FD488(void);
void func_002FDC60(void *arg0);
extern u8 D_0037E428[];
extern u8 D_0037E488[];

void func_002FDB78(void *arg0) {
    s32 temp_a0;
    s32 var_s2;

    var_s2 = 0;
    if (arg0 == NULL) {
        func_002FD2E8(arg0, D_0037E428);
        return;
    }
    if (*(u8 *)((u8 *)arg0 + 2) >= 2) {
        temp_a0 = *(s32 *)((u8 *)arg0 + 0x1C);
        if (temp_a0 != 0) {
            func_002FBB20(temp_a0);
        }
loop_7:
        func_002FC0B0();
        func_002FD488();
        func_002FDC60(arg0);
        if (*(s8 *)((u8 *)arg0 + 2) == 2) {
            var_s2 += 1;
            if (var_s2 > 0x9FFFF) {
                func_002EFAB8(D_0037E488);
            } else {
                goto loop_7;
            }
        }
        *(s32 *)((u8 *)arg0 + 0x14) = 0;
        *(u8 *)((u8 *)arg0 + 2) = 0;
    }
}
