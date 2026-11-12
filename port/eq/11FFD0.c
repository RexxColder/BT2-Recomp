#include "common.h"

#define PF32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define PU8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define PS32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern f32 D_00384094;
extern f32 D_00384098;
extern f32 D_0038409C;
extern u8 *D_003876A0;
extern u8 *D_003876A4;
extern u8 *D_00387930;

extern u8 *func_00126040(u8 *arg0);
extern s32 rand();
extern f32 func_00217330(u8 *arg0);
extern f32 BtlMember_GetHealthRatio(u8 *arg0);
extern f32 BtlMember_GetKiRatio(u8 *arg0);
extern u8 *BtlMember_GetActiveGauge(u8 *arg0);
extern s32 EftObj_UpdateMtx(u8 *arg0);
extern f32 func_0011EB68(u8 *arg0);
extern s32 func_00212878();
extern s32 func_00126058(u8 *arg0, s32 arg1, s32 arg2);
extern s32 func_0023D740(u8 *arg0, s32 arg1);
extern s32 func_0023D4E0(u8 *arg0, s32 arg1);
extern u8 *func_00240FA0(u8 *arg0, s32 arg1);
extern s32 func_0011FF78(u8 *arg0);
extern s32 func_0011FF88(u8 *arg0);
extern s32 func_0011FF98(u8 *arg0);
extern s32 func_0011FFA8(u8 *arg0);
extern s32 func_0023BD30(u8 *arg0);
extern s32 func_0023D9D0(u8 *arg0, s32 arg1);
extern s32 func_0023DAE8(u8 *arg0, s32 arg1);
extern s32 func_0020C730(s32 arg0);
extern s32 func_0020C780(s32 arg0);
extern s32 func_0020C7D0(s32 arg0);
extern s32 func_0020C820(s32 arg0);
extern s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);

/* 0x0011FFD0: condition evaluator, case a1 (0..162), parameter a2 (int, and as float via f20/f21). */
s32 func_0011FFD0(u8 *a0, s32 a1, s32 a2) {
    u8 *s0 = a0 + 0x1080;
    u8 *v7 = func_00126040(a0);
    f32 f3 = (f32)a2;
    f32 f21 = f3 * 10.0f;
    f32 f20 = f3 * D_00384094;
    f32 f0;
    s32 r;

    switch (a1) {
    case 0:
    case 2:
        return 1;
    case 1:
        return (rand() % 100) < a2;
    case 3:
        return PS32(D_003876A0, 0xD4) == a2;
    case 4:
        return !(PS32(D_00387930, 0x20) < 30 * a2);
    case 5:
        return PS32(D_00387930, 0x20) < 30 * a2;
    case 6:
        return f21 <= PF32(s0, 0x70);
    case 7:
        return PF32(s0, 0x70) < f21;
    case 8:
        return (f3 / 180.0f) * D_00384098 <= PF32(s0, 0x7C);
    case 9:
        return PF32(s0, 0x7C) < (f3 / 180.0f) * D_0038409C;
    case 10:
        return f21 <= PF32(s0, 0x88);
    case 11:
        return PF32(s0, 0x88) < f21;
    case 12:
        f0 = func_00217330(v7);
        return f21 <= f0;
    case 13:
        f0 = func_00217330(v7);
        return f0 < f21;
    case 14:
        f0 = BtlMember_GetHealthRatio(v7);
        return f20 <= f0;
    case 15:
        f0 = BtlMember_GetHealthRatio(v7);
        return f0 < f20;
    case 16:
        f0 = BtlMember_GetKiRatio(v7);
        return f20 <= f0;
    case 17:
        f0 = BtlMember_GetKiRatio(v7);
        return f0 < f20;
    case 18:
        r = PS32(BtlMember_GetActiveGauge(v7), 0x14);
        return !(r < 100000 * a2);
    case 19:
        r = PS32(BtlMember_GetActiveGauge(v7), 0x14);
        return r < 100000 * a2;
    case 24:
        return !(PS32(s0, 0xA4) < 100000 * a2);
    case 25:
        return PS32(s0, 0xA4) < 100000 * a2;
    case 26:
        f0 = BtlMember_GetHealthRatio(v7);
        return PF32(s0, 0x9C) <= f0;
    case 27:
        f0 = BtlMember_GetHealthRatio(v7);
        return f0 < PF32(s0, 0x9C);
    case 28:
        return !(PS32(a0, 8) < a2);
    case 29:
        return PS32(a0, 8) < a2;
    case 30:
        return PS32(s0, 0x130) == a2;
    case 31:
        return (PS32(s0, 0x130) ^ a2) != 0;
    case 32:
        return (EftObj_UpdateMtx(a0) ^ a2) == 0;
    case 33:
        return (EftObj_UpdateMtx(a0) ^ a2) != 0;
    case 34:
        f0 = func_0011EB68(a0);
        return f20 <= f0;
    case 35:
        f0 = func_0011EB68(a0);
        return f0 < f20;
    case 36:
        return PS32(s0, 0x90) == a2;
    case 37:
        return (PS32(s0, 0x90) ^ a2) != 0;
    case 38:
        if ((*(s64 *)(s0 + 0x120) & 0xFFFF00000000LL) != 0) goto yes;
        goto no;
    case 39:
        return PS32(s0, 0x94) == a2;
    case 40:
        return (PS32(s0, 0x94) ^ a2) != 0;
    case 49:
        return !(PS32(a0, 0x11D8) < a2);
    case 50:
        return PS32(a0, 0x11D8) < a2;
    case 51:
        return !(PS32(a0, 0x11DC) < a2);
    case 52:
        return PS32(a0, 0x11DC) < a2;
    case 53:
        return !(PS32(a0, 0x11E0) < a2);
    case 54:
        return PS32(a0, 0x11E0) < a2;
    case 55:
        return !(PS32(a0, 0x11E4) < a2);
    case 56:
        return PS32(a0, 0x11E4) < a2;
    case 57:
        return !(PS32(a0, 0x11E8) < a2);
    case 58:
        return PS32(a0, 0x11E8) < a2;
    case 20:
        return f20 <= PF32(s0, 0x9C);
    case 22:
        return f20 <= PF32(s0, 0xA0);
    case 41:
        return f20 <= PF32(s0, 0x98);
    case 42:
        return PF32(s0, 0x98) < f20;
    case 43:
        return f20 <= PF32(s0, 0xA8);
    case 44:
        return PF32(s0, 0xA8) < f20;
    case 45:
        return f20 <= PF32(s0, 0xAC);
    case 46:
        return PF32(s0, 0xAC) < f20;
    case 47:
        return f20 <= PF32(s0, 0xB0);
    case 48:
        return PF32(s0, 0xB0) < f20;
    case 59:
        return f20 <= PF32(s0, 0xB4);
    case 60:
        return PF32(s0, 0xB4) < f20;
    case 61:
        return f20 <= PF32(s0, 0xB8);
    case 62:
        return PF32(s0, 0xB8) < f20;
    case 63:
        return f20 <= PF32(s0, 0xBC);
    case 64:
        return PF32(s0, 0xBC) < f20;
    case 65:
        return f20 <= PF32(s0, 0xC0);
    case 66:
        return PF32(s0, 0xC0) < f20;
    case 67:
        return f20 <= PF32(s0, 0xC4);
    case 68:
        return PF32(s0, 0xC4) < f20;
    case 69:
        return f20 <= PF32(s0, 0xC8);
    case 70:
        return PF32(s0, 0xC8) < f20;
    case 71:
        return f20 <= PF32(s0, 0xCC);
    case 72:
        return PF32(s0, 0xCC) < f20;
    case 73:
        return f20 <= PF32(s0, 0xD0);
    case 74:
        return PF32(s0, 0xD0) < f20;
    case 75:
        return f20 <= PF32(s0, 0xD4);
    case 76:
        return PF32(s0, 0xD4) < f20;
    case 77:
        return f20 <= PF32(s0, 0xD8);
    case 78:
        return PF32(s0, 0xD8) < f20;
    case 79:
        return f20 <= PF32(s0, 0xDC);
    case 80:
        return PF32(s0, 0xDC) < f20;
    case 81:
        return f20 <= PF32(s0, 0xE0);
    case 82:
        return PF32(s0, 0xE0) < f20;
    case 83:
        return f20 <= PF32(s0, 0xE4);
    case 84:
        return PF32(s0, 0xE4) < f20;
    case 85:
        return f20 <= PF32(s0, 0xE8);
    case 86:
        return PF32(s0, 0xE8) < f20;
    case 87:
        return f20 <= PF32(s0, 0xEC);
    case 88:
        return PF32(s0, 0xEC) < f20;
    case 89:
        return f20 <= PF32(s0, 0xF0);
    case 90:
        return PF32(s0, 0xF0) < f20;
    case 91:
        return f20 <= PF32(s0, 0xF4);
    case 92:
        return PF32(s0, 0xF4) < f20;
    case 93:
        return f20 <= PF32(s0, 0xF8);
    case 94:
        return PF32(s0, 0xF8) < f20;
    case 95:
        return f20 <= PF32(s0, 0x104);
    case 96:
        return PF32(s0, 0x104) < f20;
    case 97:
        return f20 <= PF32(s0, 0x108);
    case 98:
        return PF32(s0, 0x108) < f20;
    case 99:
        return f20 <= PF32(s0, 0x10C);
    case 100:
        return PF32(s0, 0x10C) < f20;
    case 101:
        return f20 <= PF32(s0, 0x110);
    case 102:
        return PF32(s0, 0x110) < f20;
    case 103:
        return f20 <= PF32(s0, 0x114);
    case 104:
        return PF32(s0, 0x114) < f20;
    case 105:
        return !(PS32(v7, 0x1510) < a2);
    case 106:
        return PS32(v7, 0x1510) < a2;
    case 107:
        return !(PS32(s0, 0x118) < a2);
    case 108:
        return PS32(s0, 0x118) < a2;
    case 109:
        if (func_00212878(v7)) goto yes;
        goto no;
    case 110:
        if (func_00126058(a0, 0, 0x400000)) goto yes;
        goto no;
    case 111:
        return PS32(D_003876A4, 0x484) == a2;
    case 112:
        return !(PS32(D_003876A4, 0x484) < a2);
    case 113:
        return !(a2 < PS32(D_003876A4, 0x484));
    case 114:
        if (func_0023D740(v7, 0)) goto yes;
        goto no;
    case 115:
        if (func_0023D740(v7, 1)) goto yes;
        goto no;
    case 116:
        if (func_0023D4E0(v7, 2)) goto yes;
        goto no;
    case 117:
        if (func_0023D4E0(v7, 3)) goto yes;
        goto no;
    case 118:
        if (func_0023D4E0(v7, 4)) goto yes;
        goto no;
    case 119:
        if (func_0011FF78(func_00240FA0(v7, 0))) goto yes;
        goto no;
    case 120:
        if (func_0011FF78(func_00240FA0(v7, 1))) goto yes;
        goto no;
    case 121:
        if (func_0011FF88(func_00240FA0(v7, 0))) goto yes;
        goto no;
    case 122:
        if (func_0011FF88(func_00240FA0(v7, 1))) goto yes;
        goto no;
    case 123:
        if (func_0011FF98(func_00240FA0(v7, 0))) goto yes;
        goto no;
    case 124:
        if (func_0011FF98(func_00240FA0(v7, 1))) goto yes;
        goto no;
    case 125:
        if (func_0011FFA8(func_00240FA0(v7, 0))) goto yes;
        goto no;
    case 126:
        if (func_0011FFA8(func_00240FA0(v7, 1))) goto yes;
        goto no;
    case 127:
        if (PS32(s0, 0x0) & 0xA) goto yes;
        goto no;
    case 128:
        if (PS32(s0, 0x4) & 0xA) goto yes;
        goto no;
    case 129:
        if (PS32(s0, 0x8) & 0xA) goto yes;
        goto no;
    case 130:
        if (PS32(s0, 0xC) & 0xA) goto yes;
        goto no;
    case 131:
        if (PS32(s0, 0x10) & 0xA) goto yes;
        goto no;
    case 132:
        if (PS32(s0, 0x14) & 0xA) goto yes;
        goto no;
    case 133:
        if (PS32(s0, 0x18) & 0xA) goto yes;
        goto no;
    case 134:
        if (PU8(s0, 0x148)) goto yes;
        goto no;
    case 135:
        if (PS32(s0, 0x138) + PS32(s0, 0x13C) > 0) goto yes;
        goto no;
    case 136:
        if (PS32(s0, 0x144) + PS32(s0, 0x140) > 0) goto yes;
        goto no;
    case 137:
        if (func_0023BD30(v7)) goto yes;
        goto no;
    case 138:
        if (func_0023D9D0(v7, 0)) goto yes;
        goto no;
    case 139:
        if (func_0023D9D0(v7, 1)) goto yes;
        goto no;
    case 140:
        if (func_0023D9D0(v7, 2)) goto yes;
        goto no;
    case 141:
        if (func_0023D9D0(v7, 3)) goto yes;
        goto no;
    case 142:
        if (func_0023DAE8(v7, 0)) goto yes;
        goto no;
    case 143:
        if (func_0023DAE8(v7, 1)) goto yes;
        goto no;
    case 144:
        if (func_0023DAE8(v7, 2)) goto yes;
        goto no;
    case 145:
        if (func_00126058(a0, 0, 0x800)) goto yes;
        goto no;
    case 146:
        if (PS32(s0, 0x8C) & 1) goto yes;
        goto no;
    case 147:
        r = func_0020C730(PS32(a0, 0));
        r = r + func_0020C780(PS32(a0, 0));
        r = r + func_0020C7D0(PS32(a0, 0));
        r = r + func_0020C820(PS32(a0, 0));
        if (r > 0) goto yes;
        goto no;
    case 148:
        if (PS32(s0, 0x8C) & 2) goto yes;
        goto no;
    case 149:
        if (PU8(s0, 0x20)) goto yes;
        goto no;
    case 150:
        if (func_00126058(a0, 0, 1)) goto yes;
        goto no;
    case 151:
        if (PS32(v7, 0xB8C) > 0) goto no2;
        if (func_00211310(v7, 0, 1)) goto no2;
        goto yes;
    case 152:
        if (func_00126058(a0, 0, 2)) goto yes;
        goto no;
    case 153:
        if (PS32(s0, 0x8C) & 4) goto yes;
        goto no;
    case 154:
        if (func_00126058(a0, 0, 4)) goto yes;
        goto no;
    case 155:
        if (PS32(s0, 0x8C) & 8) goto yes;
        goto no;
    case 156:
        if (func_00126058(a0, 0, 0x4000)) goto yes;
        goto no;
    case 157:
        if (PS32(s0, 0x8C) & 0x10) goto yes;
        goto no;
    case 158:
        if (func_00126058(a0, 0, 0x400)) goto yes;
        goto no;
    case 159:
        if (func_00126058(a0, 1, 1)) goto yes;
        goto no;
    case 160:
        return !(PS32(s0, 0x11C) < 30 * a2);
    case 161:
        return PS32(s0, 0x11C) < 30 * a2;
    case 162:
        if (func_00126058(a0, 15, 1)) goto yes;
        goto no;
    default:
        return 0;
    }
yes:
    return a2 != 0;
no:
    return a2 == 0;
no2:
    return a2 == 0;
}
