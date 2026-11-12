#include "common.h"

s32 BtlFacade_AreBothInterruptible(void);
s32 BtlFacade_AreBothInterruptible_20EC60(void);
s32 func_0020F218(s32 state);
s32 func_0020F7A8(s32 state);
void func_0020EC08(s32 arg0);
void func_0020EC98(s32 arg0);
extern u8 *D_00387930;

/* 0x0020F9D8: state word S = D_00387930+0x30. S == 0: AreBoth -> 1; AreBoth_20EC60 -> 6. States 0..8 (table): 0 -> EC08(0),
 * EC08(1), EC98(0), EC98(1); 1..5 -> S = F218(); unless AreBoth, EC08(0), EC08(1), S = 0; 6..8 -> S = F7A8(). */
void func_0020F9D8(void) {
    s32 st;
    u8 *s;

    s = D_00387930 + 0x30;
    st = *(s32 *)s;
    if (st == 0) {
        if (BtlFacade_AreBothInterruptible() != 0) {
            *(s32 *)s = 1;
        }
        if (BtlFacade_AreBothInterruptible_20EC60() != 0) {
            *(s32 *)s = 6;
            st = 6;
        } else {
            st = *(s32 *)s;
        }
    }
    if ((u32)st >= 9) {
        return;
    }
    switch (st) {
    case 0:
        func_0020EC08(0);
        func_0020EC08(1);
        func_0020EC98(0);
        func_0020EC98(1);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        *(s32 *)s = func_0020F218(st); /* asm: a0 = the state */
        if (BtlFacade_AreBothInterruptible() != 0) {
            return;
        }
        func_0020EC08(0);
        func_0020EC08(1);
        *(s32 *)s = 0;
        break;
    case 6:
    case 7:
    case 8:
        *(s32 *)s = func_0020F7A8(st);
        break;
    }
}
