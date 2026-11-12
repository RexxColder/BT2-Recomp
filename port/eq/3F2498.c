#include "common.h"

extern u8 *D_0042A570 __attribute__((section(".data")));

s32 func_1018B8(void);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x003F2498: state st = D_0042A570->0x36CC. 1: st = 2, func_2493C0(0, 0x37A6, 0x3BBF, 0, 0x10). 2: if func_1018B8() == 5,
 * st += 1; else with v = word at 0x003B0C34: bit 0x4000 -> st = 3, func_297FE0(0, 1, 0x40, 0x40, 1); else bit 0x1000 ->
 * st = 3, func_297FE0(0, 2, 0x40, 0x40, 1). 3: func_243A80(0,0,0), st = 0. Others: nothing. */
void func_003F2498(void) {
    s32 st;
    s32 v;

    st = *(s32 *)(D_0042A570 + 0x36CC);
    switch (st) {
    case 1:
        *(s32 *)(D_0042A570 + 0x36CC) = 2;
        func_2493C0(0, 0x37A6, 0x3BBF, 0, 0x10);
        return;
    case 2:
        if (func_1018B8() == 5) {
            *(s32 *)(D_0042A570 + 0x36CC) = *(s32 *)(D_0042A570 + 0x36CC) + 1;
        } else {
            v = *(s32 *)0x003B0C34;
            if (v & 0x4000) {
                *(s32 *)(D_0042A570 + 0x36CC) = 3;
                func_297FE0(0, 1, 0x40, 0x40, 1);
            } else if (v & 0x1000) {
                *(s32 *)(D_0042A570 + 0x36CC) = 3;
                func_297FE0(0, 2, 0x40, 0x40, 1);
            }
        }
        return;
    case 3:
        func_243A80(0, 0, 0);
        *(s32 *)(D_0042A570 + 0x36CC) = 0;
        return;
    default:
        return;
    }
}
