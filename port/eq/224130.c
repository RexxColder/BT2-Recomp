#include "common.h"
void bt2_fightlog_note(const char *fmt, ...);

/* 0x00224130: per-frame state handler for a battle character (states 0xFD, 0x100-0x10B, 0x191, 0x192). */
s32 BtlObjXf_Update(u8 *obj);
s32 BtlPad_Test48(u8 *obj, s32 btn);
s32 BtlPad_Test4C(u8 *obj, s32 btn);
void BtlAnim_SetBlend(u8 *obj, f32 blend);
void BtlChar_SetVibration(u8 *obj, f32 a, f32 b);
s32 BtlMember_IsKiEmpty(u8 *obj);
u8 *BtlChar_GetPos(u8 *obj);
s32 func_001F9D78(u8 *obj, s32 state);
s32 func_001F9FB0(u8 *obj, s32 arg);
s32 func_001FA0A0(u8 *obj, s32 state, s32 arg);
s32 func_001FA110(u8 *obj, s32 arg);
s32 func_00203888(u8 *obj, s32 a, s32 b);
void func_00206958(u8 *obj, s64 flags);
s32 func_00211310(u8 *obj, s32 a, s32 b);
s32 func_002113C0(u8 *obj, s32 a, s32 b, s32 c);
s32 func_00212DD8(u8 *obj, s32 a);
s32 func_00215068(u8 *obj, s32 a, s32 b, f32 f0, f32 f1);
s32 func_00215E88(u8 *obj, s32 a, f32 f0);
s32 func_00216208(u8 *obj, f32 f0, f32 f1);
s32 func_00216678(u8 *obj);
s32 func_0023FB68(u8 *obj);
f32 func_0029DFD0(u8 *pos);

extern f32 D_00386128;
extern f32 D_0038612C;
extern f32 D_00386130;
extern f32 D_00386134;
extern f32 D_00386138;
extern f32 D_0038613C;
extern f32 D_00386140;
extern f32 D_00386144;
extern f32 D_00386148;
extern f32 D_0038614C;
extern f32 D_00386150;
extern f32 D_00386154;

s32 func_00224130(u8 *obj) {
    s32 *counter = (s32 *)(obj + 0x8C0);
    s32 state;
    s32 next;
    s32 pos_state;
    f32 scale;

    *(u32 *)(obj + 0x8DC) &= ~1u;
    state = BtlObjXf_Update(obj);

    switch (state) {
    case 0x101:
    case 0x103:
    case 0x105:
    case 0x107:
    case 0x109:
        if (func_00211310(obj, 4, 0x200) != 0) {
            func_001F9D78(obj, BtlObjXf_Update(obj));
        } else if (func_00211310(obj, 4, 0x200) != 0) {
            func_001F9D78(obj, 0x10B);
        } else {
            s32 cur = BtlObjXf_Update(obj);
            if (func_001FA0A0(obj, cur - 1, 0) != 0) {
                BtlAnim_SetBlend(obj, D_00386130);
            }
        }
        func_002113C0(obj, 6, 4, 1);
        break;
    case 0x10B:
        if (func_001FA0A0(obj, 0x100, 0) != 0) {
            BtlAnim_SetBlend(obj, D_00386134);
        }
        func_002113C0(obj, 6, 4, 1);
        break;
    case 0xFD:
        func_001F9FB0(obj, 0);
        break;
    case 0x191:
        func_001FA0A0(obj, 0x192, 1);
        *(u32 *)(obj + 0x8DC) &= ~2u;
        next = func_0023FB68(obj);
        func_00203888(obj, next, 0);
        func_002113C0(obj, 13, 8, 1);
        break;
    case 0x192:
        func_001FA110(obj, 0);
        *(u32 *)(obj + 0x8DC) |= 2;
        bt2_fightlog_note("B3 BIT2 224130 chr %08X", (s32)obj); /* TEMP */
        next = func_0023FB68(obj);
        func_00203888(obj, next, 0);
        func_002113C0(obj, 13, 8, 1);
        BtlChar_SetVibration(obj, D_00386138, D_0038613C);
        if (BtlPad_Test48(obj, 1) == 0) {
            BtlAnim_SetBlend(obj, D_00386140);
            func_001F9D78(obj, 0x100);
        }
        if (BtlMember_IsKiEmpty(obj) != 0) {
            BtlAnim_SetBlend(obj, D_00386144);
            func_001F9D78(obj, 0x100);
        }
        break;
    case 0x100:
    case 0x102:
    case 0x104:
    case 0x106:
    case 0x108:
        func_001FA110(obj, 0);
        *(u32 *)(obj + 0x8DC) = (*(u32 *)(obj + 0x8DC) | 1) & ~2u;
        *counter = *counter + 1;
        switch (BtlObjXf_Update(obj) - 0x100) {
        case 0:
            if (BtlPad_Test48(obj, 8) == 0) {
                *counter = 0;
            }
            break;
        case 2:
            if (BtlPad_Test48(obj, 12) != 0) {
                *counter = 0;
            }
            break;
        case 4:
            if (BtlPad_Test48(obj, 13) != 0) {
                *counter = 0;
            }
            break;
        case 6:
            if (BtlPad_Test48(obj, 14) != 0) {
                *counter = 0;
            }
            break;
        case 8:
            if (BtlPad_Test48(obj, 15) != 0) {
                *counter = 0;
            }
            break;
        default:
            break;
        }
        if (*counter < 3) {
            if (*(s32 *)(obj + 0x8CC) > 0 && BtlPad_Test4C(obj, 1) != 0) {
                BtlAnim_SetBlend(obj, D_0038612C);
                func_001F9D78(obj, 0x191);
                func_00212DD8(obj, 12);
            }
        } else {
            s32 dir;
            if (BtlPad_Test48(obj, 12) != 0) {
                dir = 0x102;
            } else if (BtlPad_Test48(obj, 13) != 0) {
                dir = 0x104;
            } else if (BtlPad_Test48(obj, 14) != 0) {
                dir = 0x106;
            } else {
                dir = (BtlPad_Test48(obj, 15) == 0) ? 0x100 : 0x108;
            }
            func_001F9D78(obj, dir);
            BtlAnim_SetBlend(obj, D_00386128);
            *counter = 0;
        }
        break;
    default:
        break;
    }

    switch (BtlObjXf_Update(obj) - 0x100) {
    case 0:
    case 2:
    case 4:
    case 6:
    case 8:
        pos_state = BtlObjXf_Update(obj) + 1;
        break;
    default:
        pos_state = BtlObjXf_Update(obj);
        break;
    }

    if (func_00211310(obj, 4, 0x200) != 0) {
        func_001F9D78(obj, pos_state);
        func_002113C0(obj, 6, 4, 1);
        *counter = 0;
    } else if (func_00211310(obj, 4, 0x400) != 0) {
        func_001F9D78(obj, 0x10B);
        func_002113C0(obj, 6, 4, 1);
        func_00212DD8(obj, 0x1B);
        *counter = 0;
    } else if (func_00211310(obj, 4, 0x100000) != 0) {
        func_001F9D78(obj, pos_state);
        *counter = 0;
    }

    scale = D_00386148;
    func_00215068(obj, 5, 12, D_0038614C, scale);
    func_00215E88(obj, 7, scale);
    func_00216208(obj, 0.0f, D_00386150);
    func_00216678(obj);
    func_002113C0(obj, 9, 0x40, 1);
    func_002113C0(obj, 9, 0x200, 1);
    func_002113C0(obj, 3, 0x2000, 1);
    func_002113C0(obj, 1, 0x400, 1);
    if (func_00211310(obj, 0, 4) != 0) {
        u8 *pos = BtlChar_GetPos(obj);
        if (D_00386154 < func_0029DFD0(pos + 0x50)) {
            func_00206958(obj, 0x800000000LL);
        }
    }
    if (func_00211310(obj, 0, 0x100) != 0) {
        func_002113C0(obj, 0, 2, 1);
    }
    if ((*(u32 *)(obj + 0x8DC) & 2) != 0) {
        return func_002113C0(obj, 3, 0x200000, 1);
    }
    return 0;
}
