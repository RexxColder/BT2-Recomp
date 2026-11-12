#include "common.h"

void func_002EFAB8(void *arg0);
s32 sceSifBindRpc(void *arg0, s32 arg1, s32 arg2);
extern s32 D_003553D4;
extern s32 D_003553EC;
extern u8 D_00355C70[];
extern u8 D_0037E240[];

void func_002FCFE8(void) {
    s32 temp_a1;
    s32 var_v0;

    if (D_003553EC == 0) {
        temp_a1 = D_003553D4;
loop_2:
        if (sceSifBindRpc(D_00355C70, temp_a1, 0) >= 0) {
            if (*(s32 *)(D_00355C70 + 0x24) == 0) {
                var_v0 = 0xFFFB;
loop_10:
                if (var_v0 != -1) {
                    var_v0 -= 4;
                    goto loop_10;
                }
                temp_a1 = D_003553D4;
                goto loop_2;
            }
            D_003553EC += 1;
            return;
        }
        func_002EFAB8(D_0037E240);
loop_6:
        goto loop_6;
    }
    D_003553EC += 1;
}
