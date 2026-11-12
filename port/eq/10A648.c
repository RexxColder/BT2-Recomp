#include "common.h"

extern u8 *D_003876A0;
s32 func_0010AC08(s32 arg0);
void func_00105B70(s32 arg0, s32 arg1);
s32 func_0020BF00(s32 arg0);
void func_0010B4F8(void);
s32 func_001066E8(s32 arg0, s32 arg1);
s32 func_00105BA8(void);
void func_00101740(void);
s32 BattleResult_IsAborted(void);

/* 0x0010A648: arg0 = {callback, argument}. State obj+0xB8 == 6: func_0010AC08(arg) != 0 -> func_00105B70(8, 0x10).
 * Otherwise st == 4 -> func_0020BF00(0) != 0 -> func_0010B4F8(); then func_001066E8(*(arg+4), 0) == 0 -> callback(arg)
 * != 0 -> flip 0x100 in obj+0x4D8 and func_00101740(). Finally func_00105BA8() == 0 -> 3; state 6 -> 6;
 * BattleResult_IsAborted() == 0 -> 4, else 6. */
s32 func_0010A648(s32 *arg0) {
    s32 st;
    s32 r;

    st = *(s32 *)(D_003876A0 + 0xB8);
    if (st == 6) {
        if (func_0010AC08(arg0[1]) != 0) {
            func_00105B70(8, 0x10);
        }
    } else {
        if (st == 4) {
            if (func_0020BF00(0) != 0) {
                func_0010B4F8();
            }
        }
        if (func_001066E8(*(s32 *)(arg0[1] + 4), 0) == 0) {
            if (arg0[0] != 0) {
                r = ((s32 (*)(s32))arg0[0])(arg0[1]);
                if (r != 0) {
                    *(s32 *)(D_003876A0 + 0x4D8) ^= 0x100;
                    func_00101740();
                }
            }
        }
    }
    if (func_00105BA8() == 0) {
        return 3;
    }
    if (*(s32 *)(D_003876A0 + 0xB8) == 6) {
        return 6;
    }
    return (BattleResult_IsAborted() == 0) ? 4 : 6;
}
