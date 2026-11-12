#include "common.h"

s32 func_00217488(s32 arg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
void *BtlChar_GetPos(void *arg0);
void BtlAnim_SetNoBlend(s32 arg0);
void func_0020FC38(u8 *arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
extern f32 D_00386940 __attribute__((section(".data")));

/* 0x00233FE8: v = func_00217488(arg0). For v - 0xD0 in 0..5: 0 -> code 0x132, 1 -> 0x154, 2 -> 0x176, and 3..5 do
 * the same with 0x132, 0x154, 0x176 after setting bit 0x1 of the word at +0x8DC; other v: code 0. Then
 * BattleSide_SetChara(arg0, code); the words +0xC0 of BtlChar_GetPos(arg0) and +0xC4 of a second BtlChar_GetPos are
 * zeroed; BtlAnim_SetNoBlend(arg0); func_0020FC38(arg0, 0x12) when bit 0x1 of +0x8DC is set; and finally, when the
 * byte at +0xABA is non-zero, func_00215068(arg0, 1, 0xC, D_00386940, 1.0f). */
void func_00233FE8(u8 *arg0) {
    s32 v;
    u32 k;
    s32 code = 0;
    u8 *p;

    v = func_00217488((s32)arg0);
    k = (u32)(v - 0xD0);
    if (k < 6) {
        switch (k) {
            case 0:
                code = 0x132;
                break;
            case 1:
                code = 0x154;
                break;
            case 2:
                code = 0x176;
                break;
            case 3:
                *(s32 *)(arg0 + 0x8DC) |= 1;
                code = 0x132;
                break;
            case 4:
                *(s32 *)(arg0 + 0x8DC) |= 1;
                code = 0x154;
                break;
            case 5:
                *(s32 *)(arg0 + 0x8DC) |= 1;
                code = 0x176;
                break;
        }
    }
    BattleSide_SetChara((s32)arg0, code);
    p = (u8 *)BtlChar_GetPos(arg0);
    *(s32 *)(p + 0xC0) = 0;
    p = (u8 *)BtlChar_GetPos(arg0);
    *(s32 *)(p + 0xC4) = 0;
    BtlAnim_SetNoBlend((s32)arg0);
    if (*(s32 *)(arg0 + 0x8DC) & 1) {
        func_0020FC38(arg0, 0x12);
    }
    if (*(u8 *)(arg0 + 0xABA) != 0) {
        func_00215068((s32)arg0, 1, 0xC, D_00386940, 1.0f);
    }
}
