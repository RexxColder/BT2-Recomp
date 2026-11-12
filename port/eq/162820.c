#include "common.h"

s32 func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
void func_00152960(u8 *arg0, u8 *arg1);
void func_001632E0(u8 *arg0, u8 *arg1);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_0012D3A0(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
f32 func_0020A068(s32 arg0);
void func_00129C28(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00151FB0(u8 *arg0);
s32 func_00162518(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00152200(u8 *arg0, u8 *arg1);
s32 BtlTask_SetDead(s32 arg0);
void func_00152930(s32 arg0, s32 arg1);
void func_00162350(u8 *arg0);
void func_00163BD8(u8 *arg0);
void func_00163EA0(u8 *arg0);
void func_002837C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283800(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283770(s32 arg0, void *arg1, s32 arg2);

#define FLAGS(st) (*(u32 *)(st))

/* Shot task update, variant of 0x00167AE8 (arg0 = task; state at arg0+0x38, state byte at arg0+1):
   state machine 0..5 for the shooting character, then (for the 0x173 action) sets the light colors
   from the float at +0xAB0, updates task flags and kills / advances the task. */
void func_00162820(u8 *arg0) {
    s32 advance = 0;
    u8 *st;
    u8 *ch;
    s32 owner;
    u8 *vec;
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
    func_001632E0(ch, st + 0x860);

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
                arg0[1] = 1;
            }
            break;
        case 2:
            *(f32 *)(st + 0x20) = func_0020A068(*(s32 *)ch);
            *(f32 *)(st + 0x18) = *(f32 *)(st + 0x14) * (*(f32 *)(st + 0x20) * 0.5f + 1.0f);
            func_00208DE8(*(s32 *)ch, st + 0x40, *(s32 *)(st + 4));
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
                func_0012D3A0((s32)(st + 0x30), (s32)(st + 0x80), *(s32 *)ch);
                func_00129BD0((s32)(st + 0xA0), (s32)(st + 0x30), *(f32 *)(st + 0x10));
                arg0[1] = 3;
            }
            break;
        case 4:
            func_00129C28((s32)(st + 0x90), (s32)(st + 0x80));
            func_00208DE8(*(s32 *)ch, st + 0x50, *(s32 *)(st + 8));
            Vec3_Normalize((s32)(st + 0xA0), (s32)(st + 0xA0));
            func_00129BD0((s32)(st + 0xA0), (s32)(st + 0xA0), 60.0f);
            Vec3_Add((s32)(st + 0x80), (s32)(st + 0x50), (s32)(st + 0xA0));
            if (**(s32 **)(ch + 0x20) == 0x173) {
                func_00163BD8(arg0);
            } else {
                func_00163EA0(arg0);
            }
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

    if (**(s32 **)(ch + 0x20) == 0x173) {
        f32 level = *(f32 *)(st + 0xAB0);
        s32 c1 = (s32)(level * 8.0f);
        s32 c2 = (s32)(level * 64.0f);
        s32 c3 = (s32)(level * 128.0f);

        func_002837C0(0, 0x80, 0x80, 0x80, c1 & 0xFF);
        func_00283800(0, 0x80, 0x80, 0x80, c2 & 0xFF);
        func_00283840(0, 0x80, 0x80, 0x80, c3 & 0xFF);
        func_00283770(0, st + 0x30, 0);
    }

    if (EftShot_TestBits(*(s32 *)ch, 0x80) != 0 || (FLAGS(st) & 0x400) != 0) {
        flags = FLAGS(st);
        if ((flags & 8) == 0) {
            flags |= 4;
            FLAGS(st) = flags;
        }
        FLAGS(st) = flags | 1;
    }
    vec = st + 0xB4;
    func_00151FB0(vec);
    func_00162518(*(s32 *)ch, (s32)arg0, owner, 0);
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
        func_00162350(arg0);
    }
}
