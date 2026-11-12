#include "common.h"

extern f32 D_00385874;

u8 *func_00211288(u8 *arg0);
s32 func_001FD1F0(void *arg0);
u8 *BtlChar_GetPos(u8 *arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00212820(u8 *a0);
void func_001FED88(u8 *arg0, u8 *arg1);
s32 func_0023E520(u8 *self);
void func_001FE698(u8 *arg0, u8 *arg1);
s32 BattleResult_GetFlags(u8 *arg0);
s32 BtlPad_Test48(u8 *arg0, s32 arg1);
s32 func_0023F330(u8 *arg0);
s32 func_0023F350(u8 *arg0);
s32 func_0023F370(u8 *arg0);
s32 func_0023F390(u8 *arg0);
s32 func_0023F3B0(u8 *arg0);
s32 func_0023F3D0(u8 *arg0);
void func_001FE828(void *arg0, void *arg1);
void func_001FE9F0(u8 *arg0, u8 *arg1);
s32 func_001FEB28(u8 *arg0, u8 *arg1);
void func_001FEC50(u8 *arg0, u8 *arg1);
void func_001FEED0(u8 *arg0, u8 *arg1);
void func_001FE4F8(u8 *arg0, u8 *arg1);
f32 func_0023F238(u8 *arg0);
f32 func_0023F258(u8 *arg0);
s32 func_001FBE80(u8 *arg0, f32 farg0, f32 farg1);
void BtlChar_Vibrate(u8 *a0, f32 f12, f32 f13);

/* 0x001FF008: battle-character "state pick": self = a0, opponent = func_00211288(a1). Returns 1 when nothing happened
   (or the facing check passes), 0 when an action was started. */
s32 func_001FF008(u8 *self, u8 *arg1) {
    u8 *opp;
    u8 *pos;
    s32 mode;
    s32 act = 0;
    s32 hit;
    s32 r;
    f32 a;
    f32 vib0;
    f32 vib1;
    f32 half;

    opp = func_00211288(arg1);
    mode = func_001FD1F0(opp);
    if (mode != 9) {
        pos = BtlChar_GetPos(opp);
        a = *(f32 *)(BtlChar_GetPos(opp) + 0x94);
        a = *(f32 *)(pos + 0x14) + a;
        a = BtlUtil_WrapAngle(a);
        a = a - *(f32 *)(BtlChar_GetPos(self) + 0xB4);
        a = BtlUtil_WrapAngle(a);
        if (__builtin_fabsf(a) < D_00385874) {
            return 1;
        }
    }
    if (func_00211310(opp, 3, 0x2000) != 0 && *(s32 *)(opp + 0x116C) > 0) {
        if (func_00212820(opp) != 0) {
            func_001FED88(self, opp);
            return 0;
        }
    }
    if (func_00211310(opp, 3, 0x40000) != 0) {
        if ((u32)func_0023E520(self) < 0xA) {
            func_001FE698(self, opp);
            return 0;
        }
    }
    if (func_00211310(opp, 3, 0x4000) != 0 && (BattleResult_GetFlags(self) & 0x10) != 0 && func_00212820(opp) != 0 &&
        BtlPad_Test48(opp, 2) != 0) {
        hit = 0;
        if (BtlPad_Test48(opp, 0xC) != 0) {
            r = func_0023F350(self);
            if (r == 0 || r == 2) {
                hit = 1;
            }
        }
        if (BtlPad_Test48(opp, 0xD) != 0) {
            r = func_0023F370(self);
            if (r == 0 || r == 2) {
                hit = 1;
            }
        }
        if (BtlPad_Test48(opp, 0xE) != 0) {
            r = func_0023F390(self);
            if (r == 0 || r == 2) {
                hit = 1;
            }
        }
        if (BtlPad_Test48(opp, 0xF) != 0) {
            r = func_0023F350(self);
            if (r == 0 || r == 2) {
                hit = 1;
            }
        }
        if (BtlPad_Test48(opp, 8) == 0) {
            r = func_0023F330(self);
            if (r == 0 || r == 2) {
                hit = 1;
            }
        }
        if (hit != 0) {
            func_001FE828(self, opp);
            return 0;
        }
    }
    if (mode == 0) {
        return 1;
    }
    switch (mode) {
    case 1:
    case 8:
        act = func_0023F330(self);
        break;
    case 2:
        act = func_0023F390(self);
        break;
    case 3:
        act = func_0023F3B0(self);
        break;
    case 4:
        act = func_0023F350(self);
        break;
    case 5:
        act = func_0023F370(self);
        break;
    case 6:
    case 9:
        act = 0;
        break;
    case 7:
        act = func_0023F3D0(self);
        break;
    default:
        break;
    }
    if (act == 3) {
        return 1;
    }
    if (act == 1) {
        func_001FE9F0(self, opp);
    } else if (act == 2) {
        func_001FEB28(self, opp);
    } else if (act == 4) {
        func_001FEC50(self, opp);
    } else if (act == 0) {
        if (mode == 8) {
            func_001FEED0(self, opp);
        } else {
            func_001FE4F8(self, opp);
        }
    }
    vib0 = func_0023F238(self);
    vib1 = func_0023F258(self);
    if ((BattleResult_GetFlags(self) & 0x800) != 0) {
        func_001FBE80(self, vib0, vib1);
    }
    half = 0.5f;
    func_001FBE80(opp, vib0, vib1);
    vib1 = vib1 * half;
    vib0 = vib0 * half;
    BtlChar_Vibrate(self, vib0, vib1);
    BtlChar_Vibrate(opp, vib0, vib1);
    return 0;
}
