#include "common.h"

s32 func_002A86E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
extern u8 *D_00387F2C;
extern u8 func_00104990[] __attribute__((section(".data")));

void func_00104C10(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[8];
    s32 flag;
    s32 q1;
    s32 q2;
    s32 choiceA;
    s32 choiceB;
    s32 t2;

    q1 = arg1 / 9;
    q2 = arg2 / 9;
    flag = *(s32 *)(D_00387F2C + 0x1008) & 1;
    sp[0] = 0;
    sp[1] = 0x33D3;
    sp[2] = arg0 + 0x33D4;
    choiceA = (flag == 0) ? (q1 + 0xABA3) : (q1 + 0xAC2F);
    sp[3] = choiceA;
    t2 = q2 + 0xABA3;
    choiceB = (flag == 0) ? (q2 + 0xABA3) : (q2 + 0xAC2F);
    sp[4] = choiceB;
    func_002A86E8((s32)sp, (s32)func_00104990, 0, q1 + 0xABA3, choiceA, 9, t2, (s32)D_00387F2C);
}
