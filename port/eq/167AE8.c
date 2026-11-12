#include "common.h"

s32 func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
void func_00152960(u8 *arg0, u8 *arg1);
void func_00152530(u8 *arg0, u8 *arg1);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_0012D3A0(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
f32 func_0020A068(s32 arg0);
void func_00129C28(s32 arg0, s32 arg1);
s32 func_0012D488(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_0012D5D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void func_00129C38(s32 arg0, s32 arg1);
void func_00151FB0(u8 *arg0);
void func_00167870(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00152200(u8 *arg0, u8 *arg1);
s32 BtlTask_SetDead(s32 arg0);
void func_00152930(s32 arg0, s32 arg1);
void func_001676A8(u8 *arg0);

#define FLAGS(st) (*(u32 *)(st))

/* Shot task update (arg0 = task; its state is at arg0+0x38, state byte at arg0+1): runs the state machine
   0..5 that tracks the shooting character's joints (positions, direction, speed), then updates the
   task flags and kills / advances it. */
void func_00167AE8(u8 *arg0) {
    u8 sp[0x10];
    s32 advance = 0;
    u8 *st;
    u8 *ch;
    s32 owner;
    u8 *effect;
    u8 *vec;
    s32 anim;
    s32 chr;
    u32 flags;
    s32 busy;

    owner = *(s32 *)(func_001F3758((s32)arg0) + 0x38);
    st = *(u8 **)(arg0 + 0x38);
    ch = *(u8 **)(st + 0xB0);
    if (BtlScene_IsCharStopped(*(s32 *)ch) != 0) {
        return;
    }
    if (*(s32 *)(*(u8 **)(ch + 0x20) + 4) == 0) {
        func_00152960(*(u8 **)ch, ch);
    }
    func_00152530(ch, st + 0x860);

    if ((FLAGS(st) & 0x80) == 0) {
        if (EftShot_TestBits(*(s32 *)ch, 2) != 0) {
            arg0[1] = 0;
            FLAGS(st) |= 0x80;
        } else if (EftShot_TestBits(*(s32 *)ch, 4) != 0) {
            arg0[1] = 2;
            FLAGS(st) |= 0x80;
        }
    }

    if ((FLAGS(st) & 0x80) != 0 && arg0[1] < 6) {
        switch (arg0[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)ch, 2) != 0) {
                *(s32 *)(st + 4) = *(s32 *)(st + 0x870);
                func_00208DE8(*(s32 *)ch, st + 0x40, *(s32 *)(st + 0x870));
                func_0012D3A0((s32)(st + 0x30), (s32)(st + 0x40), *(s32 *)ch);
                if ((FLAGS(st) & 0x200) != 0) {
                    func_00208DE8(*(s32 *)ch, sp, 0x30);
                    Vec3_Sub((s32)(st + 0x30), (s32)(st + 0x40), (s32)sp);
                    Vec3_Normalize((s32)(st + 0x30), (s32)(st + 0x30));
                }
                arg0[1] = 1;
            }
            break;
        case 2:
            *(f32 *)(st + 0x20) = func_0020A068(*(s32 *)ch);
            *(f32 *)(st + 0x18) = *(f32 *)(st + 0x14) * (*(f32 *)(st + 0x20) * 0.5f + 1.0f);
            func_00208DE8(*(s32 *)ch, st + 0x40, *(s32 *)(st + 4));
            if ((FLAGS(st) & 0x200) != 0) {
                func_00208DE8(*(s32 *)ch, sp, 0x30);
                Vec3_Sub((s32)(st + 0x30), (s32)(st + 0x40), (s32)sp);
                Vec3_Normalize((s32)(st + 0x30), (s32)(st + 0x30));
            }
            if (EftShot_TestBits(*(s32 *)ch, 0x40) != 0) {
                *(s32 *)(st + 0xC) = *(s32 *)(st + 0x9B0);
                func_00208DE8(*(s32 *)ch, st + 0x60, *(s32 *)(st + 0x9B0));
                FLAGS(st) |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)ch, 4) != 0) {
                flags = FLAGS(st);
                *(s32 *)(st + 8) = *(s32 *)(st + 0x8B0);
                FLAGS(st) = flags | 0x10;
                func_00208DE8(*(s32 *)ch, st + 0x50, *(s32 *)(st + 0x8B0));
                func_00129C28((s32)(st + 0x70), (s32)(st + 0x50));
                func_00129C28((s32)(st + 0x80), (s32)(st + 0x70));
                func_00208DE8(*(s32 *)ch, st + 0x90, 0x11);
                func_0012D488(ch, st + 0x30, (s32)(st + 0x80), *(s32 *)ch);
                func_00129BD0((s32)(st + 0xA0), (s32)(st + 0x30), *(f32 *)(st + 0x10));
                arg0[1] = 3;
            }
            break;
        case 4:
            func_00129C28((s32)(st + 0x90), (s32)(st + 0x80));
            if ((*(u32 *)(*(u8 **)(*(u8 **)(st + 0xB0) + 0x20) + 0x30) & 2) == 0) {
                if ((FLAGS(st) & 0x20) != 0) {
                    func_00129C38((s32)(st + 0x80), (s32)(arg0 + 0x10));
                } else {
                    f32 spd = *(f32 *)(*(u8 **)(ch + 0x24) + 0x10);

                    if (0.0f < spd) {
                        func_0012D5D8((s32)(st + 0x30), (s32)(st + 0x80), (s32)(st + 0x30), *(s32 *)ch,
                                      *(f32 *)(st + 0x10), spd);
                        func_00129BD0((s32)(st + 0xA0), (s32)(st + 0x30), *(f32 *)(st + 0x10));
                    }
                    Vec3_Add((s32)(st + 0x80), (s32)(st + 0x80), (s32)(st + 0xA0));
                }
            }
            func_00208DE8(*(s32 *)ch, st + 0x50, *(s32 *)(st + 8));
            if (EftShot_TestBits(*(s32 *)ch, 8) != 0) {
                FLAGS(st) |= 9;
                arg0[1] = 5;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        }
    }

    vec = st + 0xB4;
    if (EftShot_TestBits(*(s32 *)ch, 0x80) != 0) {
        flags = FLAGS(st);
        if ((flags & 8) == 0) {
            FLAGS(st) = flags | 4;
            flags = FLAGS(st);
        }
        FLAGS(st) = flags | 1;
    }
    func_00151FB0(vec);
    func_00167870(*(s32 *)ch, (s32)arg0, owner, 0);
    busy = func_00152200((u8 *)owner, vec) != 0;
    if (advance != 0) {
        arg0[1] = arg0[1] + 1;
    }
    flags = FLAGS(st);
    if (!busy) {
        if ((flags & 2) != 0) {
            BtlTask_SetDead((s32)arg0);
            return;
        }
    }
    if ((flags & 1) != 0) {
        FLAGS(st) = flags | 2;
    } else if ((*(u32 *)(*(u8 **)(ch + 0x20) + 0x30) & 1) != 0 && (flags & 0x10) != 0) {
        func_00152930(owner, (s32)vec);
        func_001676A8(arg0);
    }
}
