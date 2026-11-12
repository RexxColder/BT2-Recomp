#include "common.h"

s32 func_00218128(u8 *arg0, s32 arg1);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void BattleSide_SetChara(u8 *arg0, s32 arg1, s32 arg2);
void func_00217CB8(u8 *arg0);
void *BtlChar_GetPos(u8 *arg0);
f32 func_0023F048(u8 *arg0);

/* 0x00218948: obj+0x998 is a counter. func_00218128(obj, 4) != 0 -> 4 becomes 5, 9 becomes 0. func_00211310 != 0 ->
 * counter at least 5 and func_002113C0(obj, 5, 0x200, 0). Then counter = (counter+1) % 10 and BattleSide_SetChara(obj,
 * old+0x43, new). Finally the float from func_0023F048 goes to BtlChar_GetPos(obj)+0xC0. GUESS arity for func_00211310. */
void func_00218948(u8 *arg0) {
    s32 cur;
    s32 nxt;
    f32 f;
    u8 *pos;

    if (func_00218128(arg0, 4) != 0) {
        cur = *(s32 *)(arg0 + 0x998);
        if (cur == 4) {
            cur = 5;
            *(s32 *)(arg0 + 0x998) = 5;
        }
        if (cur == 9) {
            *(s32 *)(arg0 + 0x998) = 0;
        }
    }
    if (func_00211310(arg0, 5, 0x200, 4, 9) != 0) {
        if (*(s32 *)(arg0 + 0x998) < 5) {
            *(s32 *)(arg0 + 0x998) = 5;
        }
        func_002113C0(arg0, 5, 0x200, 0);
    }
    cur = *(s32 *)(arg0 + 0x998);
    nxt = cur + 1;
    *(s32 *)(arg0 + 0x998) = nxt;
    *(s32 *)(arg0 + 0x998) = nxt % 10;
    BattleSide_SetChara(arg0, cur + 0x43, nxt % 10);
    func_00217CB8(arg0);
    pos = BtlChar_GetPos(arg0);
    f = func_0023F048(arg0);
    *(f32 *)(pos + 0xC0) = f;
}
