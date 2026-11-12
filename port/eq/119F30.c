#include "common.h"

extern f32 D_00384030;
extern f32 D_00384034;
extern f32 D_00384038;
extern f32 D_0038403C;
extern f32 D_00384040;

s32 func_0010B0A0(s32 arg0);
s32 func_0020B860(u8 *arg0);
s32 func_0020B8E8(u8 *arg0);
s32 func_0020B9F8(u8 *arg0);
s32 func_0020B970(u8 *arg0);
s32 func_0020BA80(u8 *arg0);
s32 func_0020BB08(u8 *arg0);
s32 func_0020BC18(u8 *arg0);
s32 func_0020BB90(u8 *arg0);
s32 func_0020BCA0(u8 *arg0);
extern void Ramp_Start(u8 *arg0, f32 farg0, f32 farg1, f32 farg2);
extern s32 Ramp_Step(u8 *arg0);
void func_00119B90(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x00119F30: advance a pad-direction highlight state. obj (a0): +0 kind, +4 dir, +0xC fade 0..128, +0x10/+0x14 blink
   counters, +0x18 ramp (+0x28 = its value). Direction 0..7 from func_0020B860..BB90, 0x20BCA0 = "center" mode.
   Picks an entry from two 8-entry tables, then calls func_00119B90(sel+0x3BA0, obj, entry, flag, dir >= 4 ? 0 : 1 ... ). */
s32 func_00119F30(u8 *obj, s32 arg1, u8 *pad) {
    /* {entry, flag} pairs, 8 each */
    s32 tabA[16] = {3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 6, 1, 5, 1, 4, 1};
    s32 tabB[16] = {8, 9, 10, 11, 12, 13, 14, 15, 9, 9, 11, 11, 13, 13, 15, 15};
    s32 dir = -1;
    s32 active = 0;
    s32 entry = 0;
    s32 flag = 0;
    s32 center;
    s32 fade;
    s32 idx;
    s32 cnt;
    u8 *sel;
    u8 *ramp;

    sel = (u8 *)(func_0010B0A0(arg1) + 0x3BA0);
    if (func_0020B860(pad) != 0) {
        dir = 0;
    }
    if (func_0020B8E8(pad) != 0) {
        dir = 1;
    }
    if (func_0020B9F8(pad) != 0) {
        dir = 2;
    }
    if (func_0020B970(pad) != 0) {
        dir = 3;
    }
    if (func_0020BA80(pad) != 0) {
        dir = 4;
    }
    if (func_0020BB08(pad) != 0) {
        dir = 5;
    }
    if (func_0020BC18(pad) != 0) {
        dir = 6;
    }
    if (func_0020BB90(pad) != 0) {
        dir = 7;
    }
    if (func_0020BCA0(pad) != 0) {
        center = 1;
        dir = -1;
        obj[0] = 1;
        active = 1;
        *(s32 *)(obj + 4) = -1;
    } else {
        center = 0;
        if (dir < 0) {
            dir = -1;
        } else {
            obj[0] = 0;
            active = 1;
            *(s32 *)(obj + 4) = dir;
        }
    }
    fade = *(s32 *)(obj + 0xC);
    ramp = obj + 0x18;
    if (center == 0 && dir < 0) {
        /* fade out */
        fade = fade - 15;
        *(s32 *)(obj + 0xC) = fade;
        if (fade < 0) {
            Ramp_Start(ramp, D_0038403C, 0.0f, 1.0f);
            *(s32 *)(obj + 0xC) = 0;
            *(s32 *)(obj + 0x14) = 0;
            *(s32 *)(obj + 0x10) = 0;
            return 0;
        }
        if (obj[0] != 0) {
            entry = 2;
        } else if (*(s32 *)(obj + 4) >= 0) {
            entry = tabB[*(s32 *)(obj + 4) * 2];
        }
        if (Ramp_Step(ramp) != 0) {
            if (*(f32 *)(obj + 0x28) == 1.0f) {
                Ramp_Start(ramp, D_00384040, 1.0f, 0.0f);
            }
        }
    } else {
        /* fade in */
        fade = fade + 15;
        *(s32 *)(obj + 0xC) = fade;
        if (fade >= 129) {
            *(s32 *)(obj + 0xC) = 128;
        }
        if (*(s32 *)(obj + 0xC) != 128) {
            if (center != 0) {
                entry = 2;
            } else if (dir >= 0) {
                entry = tabB[dir * 2];
            }
            Ramp_Start(ramp, D_00384038, 0.0f, 1.0f);
        } else {
            if (Ramp_Step(ramp) != 0) {
                if (*(f32 *)(obj + 0x28) == 1.0f) {
                    Ramp_Start(ramp, D_00384030, 1.0f, 0.0f);
                } else {
                    Ramp_Start(ramp, D_00384034, 0.0f, 1.0f);
                }
            }
            if (center != 0) {
                idx = *(s32 *)(obj + 0x14);
                *(s32 *)(obj + 0x14) = idx + 1;
                idx = idx & 7;
                entry = tabA[idx * 2];
                flag = tabA[idx * 2 + 1] != 0;
                if (*(s32 *)(obj + 0x14) == 8) {
                    *(s32 *)(obj + 0x14) = 0;
                }
            } else if (dir >= 0) {
                idx = *(s32 *)(obj + 0x14) & 1;
                cnt = *(s32 *)(obj + 0x10);
                *(s32 *)(obj + 0x10) = cnt + 1;
                entry = tabB[dir * 2 + idx];
                if ((u32)active < (u32)cnt) {
                    *(s32 *)(obj + 0x10) = 0;
                    *(s32 *)(obj + 0x14) = *(s32 *)(obj + 0x14) + 1;
                    if (*(s32 *)(obj + 0x14) == 2) {
                        *(s32 *)(obj + 0x14) = 0;
                    }
                }
            }
        }
    }
    func_00119B90(sel, obj, entry, flag, (dir < 4) ^ 1);
    return 1;
}
