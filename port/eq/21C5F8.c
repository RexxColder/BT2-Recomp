#include "common.h"
void bt2_fightlog_note(const char *fmt, ...);

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FL(p, o) (*(f32 *)((u8 *)(p) + (o)))

extern f32 D_00385D40;
extern f32 D_00385D44;
extern f32 D_00385D48;
extern f32 D_00385D4C;
extern f32 D_00385D50;
extern f32 D_00385D54;
extern f32 D_00385D58;

f32 func_00240D50(s32 arg0, s32 arg1);
s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_001F9D78(s32 arg0, s32 arg1);
s32 func_001F9FB0(s32 arg0, s32 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
void BtlChar_SetVibration(s32 arg0, f32 farg0, f32 farg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
f32 func_001FA318(s32 arg0);
void func_00206958(s32 arg0, s64 arg1);
void *BtlChar_GetPos(void *arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217BD0(s32 arg0);
f32 func_001FA308(s32 arg0);
s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216770(s32 arg0);
void BtlMove_BrakeVertical(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_0021C5F8(u8 *arg0) {
    f32 f20;
    f32 f21;
    s32 s1;
    s32 s2;
    s32 v;

    s1 = 1;
    s2 = 0;
    f21 = func_00240D50((s32)arg0, 4);
    v = BtlObjXf_Update((s32)arg0);
    if (v == 0x7A) {
        func_001FA0A0((s32)arg0, 0x7B, 0);
    } else if (v == 0x7B) {
        if (func_001FA0A0((s32)arg0, 0x7C, 0) != 0) {
            func_0020FC38((s32)arg0, 0x2F);
            BtlChar_SetVibration((s32)arg0, 1.0f, D_00385D40);
        } else {
            if (BtlPad_Test48((s32)arg0, 0) == 0) {
                func_001F9D78((s32)arg0, 0x7C);
            }
            if (BtlPad_Test4C((s32)arg0, 3) != 0 || BtlPad_Test4C((s32)arg0, 2) != 0 ||
                BtlPad_Test4C((s32)arg0, 1) != 0) {
                W(arg0, 0x8DC) = W(arg0, 0x8DC) | 2;
                bt2_fightlog_note("B3 BIT2 21C5F8 chr %08X", (s32)arg0); /* TEMP */
                func_0020FC38((s32)arg0, 0x1F);
            }
        }
        FL(arg0, 0x9B0) = func_001FA318((s32)arg0);
        func_00206958((s32)arg0, 0x40000);
    } else if (v == 0x7C) {
        func_001F9FB0((s32)arg0, 0);
        f21 = 0.0f;
        s2 = 1;
        if (func_00211310((s32)arg0, 4, 2) != 0) {
            FL(BtlChar_GetPos(arg0), 0xC0) = f21;
        }
        if (func_00211310((s32)arg0, 4, 0xC) != 0) {
            s1 = 0;
            if (func_00217BD0((s32)arg0) != 0) {
                FL(BtlChar_GetPos(arg0), 0xC0) = f21;
            }
        }
        f20 = func_001FA308((s32)arg0) - 15.0f;
        if (f20 < (f32)BtlObjAnim_QueryEvent(W(arg0, 0x1530), 2, 0, 1)) {
            func_00206958((s32)arg0, 0x40000);
        }
    }

    if ((W(arg0, 0x8DC) & 1) && s1 != 0) {
        func_00215068((s32)arg0, 1, 0xD, D_00385D44, D_00385D48);
    } else {
        func_00215068((s32)arg0, 5, 0xD, D_00385D4C, D_00385D50);
    }
    func_00215E88((s32)arg0, 3, D_00385D54);
    func_00216208((s32)arg0, f21, D_00385D58);
    if (s2 != 0 && func_00211310((s32)arg0, 0, 2) == 0) {
        func_00216770((s32)arg0);
    } else {
        BtlMove_BrakeVertical((s32)arg0);
    }
    func_002113C0((s32)arg0, 9, 0x200, 1);
    func_002113C0((s32)arg0, 0xF, 0x40, 1);
    if (func_00211310((s32)arg0, 0, 0x100) != 0) {
        return func_002113C0((s32)arg0, 0, 2, 1);
    }
    return 0;
}
