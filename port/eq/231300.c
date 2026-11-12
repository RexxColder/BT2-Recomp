#include "m2c_macros.h"

extern void BattleSide_SetChara(s32 arg0, s32 arg1);
extern s32 BtlChar_GetPos(s32 arg0);
extern s32 BtlMember_GetActiveGauge(s32 arg0);
extern s32 func_00203888(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00203C58(s32 arg0, s64 arg1);
extern void func_00206958(s32 arg0, s64 arg1);
extern void func_0020FC38(s32 arg0, s32 arg1);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00211418(s32 arg0, s32 arg1);
extern s32 func_00212320(s32 arg0);
extern void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
extern s32 func_00217488(s32 arg0);
extern s32 func_00241718(s32 arg0, s32 arg1);
extern f32 D_0038687C;

void func_00231300(s32 arg0) {
    s32 a2;
    s32 *slot;
    s32 s1;
    s32 v;

    func_002113C0(arg0, 7, 0xFFFDFFFF, 0);
    if (func_00211310(arg0, 0, 1) != 0) {
        func_00215068(arg0, 1, 0xC, D_0038687C, 1.0f);
    }
    v = func_00217488(arg0);
    if (v == 0xAC) {
        BattleSide_SetChara(arg0, 0x11C);
        func_00206958(arg0, 1LL << 53);   /* asm 0x2313A8: li a1,0x8000; dsll32 a1,a1,6 */
        a2 = 0x1000;
        func_002113C0(arg0, 0xF, a2, 1);
        func_00211418(arg0, 0x80000);
    } else if (v == 0xAE) {
        BattleSide_SetChara(arg0, 0x182);
        func_00206958(arg0, 1LL << 55);   /* asm 0x231418: dsll32 a1,a1,8 */
        func_002113C0(arg0, 0xF, 0x4000, 1);
        func_00211418(arg0, 0x100000);
    } else if (v == 0xAD) {
        BattleSide_SetChara(arg0, 0x13E);
        func_00206958(arg0, 1LL << 54);   /* asm 0x2313D4: dsll32 a1,a1,7 */
        a2 = 0x2000;
        func_002113C0(arg0, 0xF, a2, 1);
        func_00211418(arg0, 0x80000);
    }
    s1 = func_00212320(arg0);
    func_0020FC38(arg0, 0x2B);
    if (func_00203C58(arg0, 0x10000000) != 0) {
        func_00203888(arg0, 0x186A0, 1);
    } else {
        func_00203888(arg0, func_00241718(arg0, s1), 1);
    }
    slot = (s32 *)((u8 *)BtlMember_GetActiveGauge(arg0) + ((s1 * 4) + 0x30));
    *slot = *slot + 1;
    *(s32 *)(arg0 + 0xA30) = 0;
    *(s32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC0) = 0;
    *(s32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC4) = 0;
}
