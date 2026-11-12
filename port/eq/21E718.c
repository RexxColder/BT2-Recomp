#include "common.h"

extern f32 D_00385E78;
extern f32 D_00385E7C;
extern f32 D_00385E80;
extern f32 D_00385E84;
extern f32 D_00385E88;

void func_001F9FB0(s32 arg0, s32 arg1);
void func_001F9D10(s32 arg0, s32 arg1);
void func_001F9D78(void *arg0, s32 arg1);
f32 func_00209730(s32 arg0, s32 arg1);
void func_00210FD0(s32 arg0, s32 arg1);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
s32 BtlChar_GetPos(s32 arg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_002608E8(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002163B8(void *obj, f32 ang);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
f32 func_001FA318(s32 arg0);
s32 func_001FA2E0(s32 arg0);
void func_001FA380(s32 arg0, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BtlObjXf_Update(s32 arg0);
f32 floorf(f32 farg0);

/* Per-frame update of a multi-step character action (arg0 = character): state at +0x8C0 runs 0..3
   (0: counted start-up frames, 1: set up from joint positions, 2: snap + request animation, 3: pick
   animation per BtlObjXf_Update); every path ends by setting bits 0x40 / 0x80000000000 / 0x800000. */
void func_0021E718(u8 *arg0) {
    s32 chr = (s32)arg0;
    s32 *state = (s32 *)(arg0 + 0x8C0);
    s32 *count = (s32 *)(arg0 + 0x8C4);
    s32 *animBase = (s32 *)(arg0 + 0x8C8);
    f32 *timer = (f32 *)(arg0 + 0x8D0);
    s32 advance = 0;   /* 1: go to next state */
    s32 flag;
    u8 sp[0x30];

    if (*state == 1) {
        func_00209730(*(s32 *)(arg0 + 0x1534), (s32)sp);
        func_00210FD0(chr, (s32)(sp + 0x10));
        func_00312650((s32)(sp + 0x20), (s32)(sp + 0x10), (s32)sp);
        {
            s32 posA = BtlChar_GetPos(chr);
            s32 posB = BtlChar_GetPos(chr);

            func_00312638(posA, posB, (s32)(sp + 0x20));
        }
        func_002608E8(*(s32 *)(arg0 + 0x1530));
        func_002113C0(chr, 3, 0x800, 1);
        func_002113C0(chr, 9, 0x4000, 1);
        advance = 2;
    } else if (*state < 2) {
        if (*state == 0) {
            func_001F9FB0(chr, 0);
            *count = *count + 1;
            if (*count == 1) {
                func_001F9D10(chr, *animBase);
                *timer = *timer + (*(f32 *)(*(u8 **)(arg0 + 0x1530) + 0xBDC) * 30.0f) / 60.0f;
            }
            if (*count == 2) {
                s32 ev;

                func_001F9D10(chr, *animBase + 2);
                ev = BtlObjAnim_QueryEvent(*(s32 *)(arg0 + 0x1530), 1, 1, 0);
                ev = ev + BtlObjAnim_QueryEvent(*(s32 *)(arg0 + 0x1530), 2, 1, 0);
                *timer = *timer + (((f32)ev * 0.5f) * 30.0f) / 60.0f;
            }
            if (*count >= 4) {
                func_002113C0(chr, 9, 0x4000, 1);
            }
            if (*count >= 8) {
                *count = 0;
                *state = *state + 1;
            }
        }
    } else if (*state == 2) {
        func_002163B8(arg0, floorf(*timer + 0.5f));
        func_00215068(chr, 1, 9, D_00385E78, 1.0f);
        func_00215E88(1.0f, chr, 3);
        func_002113C0(chr, 3, 0x800, 1);
        func_002113C0(chr, 9, 0x4000, 1);
        func_001F9D78(arg0, *animBase);
        func_00206958(chr, 0x4000);
        advance = 2;
    } else if (*state == 3) {
        flag = 1;
        switch (BtlObjXf_Update(chr)) {
        case 0x68:
        case 0x6B:
        case 0x6E:
        case 0x71:
        case 0x74:
            func_001FA0A0(chr, BtlObjXf_Update(chr) + 2, 0);
            *(f32 *)(arg0 + 0x9B0) = 1.0f;
            if (func_001FA318(chr) < D_00385E7C) {
                func_002113C0(chr, 9, 0x4000, 1);
            }
            if (func_001FA2E0(chr) != 0) {
                func_002113C0(chr, 0xE, 0x40, 1);
            }
            break;
        case 0x6A:
        case 0x6D:
        case 0x70:
        case 0x73:
        case 0x76:
            func_001F9FB0(chr, 0);
            *(u32 *)(arg0 + 0x8DC) |= 1;
            func_001FA380(chr, 2.0f);
            func_00211310(chr, 4, 2);
            flag = func_00211310(chr, 4, 8) == 0;
            break;
        default:
            break;
        }
        if (flag != 0) {
            func_00215068(chr, 1, 9, D_00385E80, 1.0f);
        } else {
            func_00215068(chr, 5, 0xC, D_00385E84, 0.5f);
        }
        func_00215E88(1.0f, chr, 5);
        func_00216208(chr, 0.0f, D_00385E88);
        advance = 0;
    }

    if (advance == 2) {
        func_002113C0(chr, 0xE, 0x20, 1);
        func_002113C0(chr, 0xF, 0x20, 1);
        func_002113C0(chr, 1, 0x20000, 1);
        *state = *state + 1;
    }
    func_002113C0(chr, 5, 0x40, 1);
    func_00206958(chr, 0x80000000000LL);
    func_002113C0(chr, 1, 0x800000, 1);
}
