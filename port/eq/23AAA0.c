#include "common.h"

extern s32 func_00212320(u8 *obj);
extern s32 func_00241C50(u8 *obj, s32 id);
extern s32 func_00241F80(u8 *obj, s32 id);
extern s32 func_00241C70(u8 *obj, s32 id);
extern s32 func_00241D50(u8 *obj, s32 id);
extern s32 func_00241DB0(u8 *obj, s32 id);
extern s32 func_00241C98(u8 *obj, s32 id);
extern s32 func_00241E90(u8 *obj, s32 id);
extern s32 func_00241CD0(u8 *obj, s32 id);
extern s32 func_00241D10(u8 *obj, s32 id);
extern s32 func_00241CF0(u8 *obj, s32 id);
extern s32 func_00241D30(u8 *obj, s32 id);
extern s32 func_00241FF0(u8 *obj, s32 id);
extern s32 func_00242010(u8 *obj, s32 id);
extern u8 *BtlMember_GetActiveGauge(u8 *obj);
extern s32 func_0023F980(u8 *obj);
extern void func_002113C0(u8 *obj, s32 a1, s32 a2, s32 a3);
extern s32 func_00211310(u8 *obj, s32 a1, s32 a2);
extern void BtlMember_AddMaxPower(u8 *obj, s32 amount);
extern void BtlMember_AddHealth(u8 *obj, s32 amount);
extern void func_00203310(u8 *obj, s32 amount, s32 kind);
extern void func_00203810(u8 *obj, s32 amount);
extern void func_00203888(u8 *obj, s32 amount, s32 kind);
extern s32 BtlMember_SubBlast(u8 *obj, s32 amount);
extern void func_001F9388(u8 *obj, s32 idx, s32 flag, s32 val, s32 mode);
extern void func_001F93F8(u8 *obj, s32 idx, s32 flag, s32 val, s32 mode);
extern void func_001F9428(u8 *obj, s32 idx, s32 flag, s32 val, s32 mode);
extern void func_001F9460(u8 *obj, s32 idx, s32 flag, s32 val);
extern void func_001F9480(u8 *obj, s32 idx, s32 flag, s32 val);

/* Applies the result of one attack/effect step to a battle member (health, power, blast, bonus counters). */
s32 func_0023AAA0(u8 *obj) {
    s32 id;
    s32 hasId;
    s32 code;
    s32 flags;
    s32 health;
    s32 power;
    s32 amount;
    s32 kind;
    s32 v0, v1, v2, v3, v4, v5;
    s32 bit8;
    u8 *gauge;

    id = func_00212320(obj);
    hasId = id != 0;
    code = func_00241C50(obj, id);
    flags = func_00241F80(obj, id);
    func_00241C70(obj, id);
    health = func_00241D50(obj, id);
    power = func_00241DB0(obj, id);
    amount = func_00241C98(obj, id);
    kind = func_00241E90(obj, id);
    v0 = func_00241CD0(obj, id);
    v1 = func_00241D10(obj, id);
    v2 = func_00241CF0(obj, id);
    v3 = func_00241D30(obj, id);
    v4 = func_00241FF0(obj, id);
    v5 = func_00242010(obj, id);
    bit8 = (flags >> 8) & 1;

    if (code < 0x18) {
        if (code < 0x16) {
            if (code == 10) {
                *(s32 *)(obj + 0xAD0) = id;
                *(s32 *)(obj + 0xAC8) = 1;
            } else if (code == 0x14) {
                gauge = BtlMember_GetActiveGauge(obj);
                health = -*(s32 *)gauge / 5;
            }
        } else {
            func_002113C0(obj, 8, 1, 1);
            func_002113C0(obj, 8, 2, 1);
            power = func_0023F980(obj);
            if (amount > 0) {
                *(s32 *)(obj + 0xAD4) = power / amount;
            }
        }
    } else if (code == 0xC0) {
        *(s32 *)(obj + 0xAD0) = id;
        *(s32 *)(obj + 0xAC8) = 3;
    } else if (code < 0xC1) {
        if (code == 0xBF) {
            *(s32 *)(obj + 0xAD0) = id;
            *(s32 *)(obj + 0xAC8) = 1;
        }
    } else if (code == 0xC4) {
        *(s32 *)(obj + 0xAD0) = id;
        *(s32 *)(obj + 0xACC) = 1;
    }

    if (flags & 0x200) {
        power = func_0023F980(obj);
        BtlMember_AddMaxPower(obj, 30000);
        func_002113C0(obj, 0, 0x800, 1);
        func_002113C0(obj, 0xD, 1, 1);
    }
    if (flags & 0x800000) {
        func_002113C0(obj, 0, 0x1000, 1);
    }
    if (flags & 0x800) {
        switch ((u32)kind) {
        case 1:
            *(s32 *)(obj + 0xAD8) = amount;
            break;
        case 2:
            *(u8 *)(obj + 0xAF4) = 1;
            break;
        case 3:
            *(u8 *)(obj + 0xAF5) = 1;
            break;
        default:
            break;
        }
    }
    if (flags & 0x400) {
        *(s32 *)(obj + 0xADC) = amount;
    }
    if (flags & 0x1000) {
        *(s32 *)(obj + 0xAF0) = amount;
        power = -func_0023F980(obj);
        if (func_00211310(obj, 0, 0x400) != 0) {
            func_002113C0(obj, 1, 0x4000000, 1);
        }
    }
    if (health > 0) {
        BtlMember_AddHealth(obj, health);
    }
    if (health < 0) {
        func_00203310(obj, -health, 0x1F);
    }
    if (power > 0) {
        func_00203810(obj, power);
        gauge = BtlMember_GetActiveGauge(obj);
        if (power == *(s32 *)(gauge + 0x10)) {
            func_002113C0(obj, 0xD, 0x20, 1);
        }
    }
    if (power < 0) {
        func_00203888(obj, -power, 1);
    }

    switch ((u32)kind) {
    case 0:
        func_001F9388(obj, 0, hasId, v0, bit8);
        func_001F9388(obj, 1, hasId, v1, bit8);
        func_001F9388(obj, 2, hasId, v2, bit8);
        func_001F9388(obj, 3, hasId, v3, bit8);
        break;
    case 1:
        func_001F93F8(obj, 0, hasId, v0, amount);
        func_001F93F8(obj, 1, hasId, v1, amount);
        func_001F93F8(obj, 2, hasId, v2, amount);
        func_001F93F8(obj, 3, hasId, v3, amount);
        break;
    case 2:
        func_001F9428(obj, 0, hasId, v0, bit8);
        func_001F9428(obj, 1, hasId, v1, bit8);
        func_001F9428(obj, 2, hasId, v2, bit8);
        func_001F9428(obj, 3, hasId, v3, bit8);
        break;
    case 3:
        func_001F9460(obj, 0, hasId, v0);
        func_001F9460(obj, 1, hasId, v1);
        func_001F9460(obj, 2, hasId, v2);
        func_001F9460(obj, 3, hasId, v3);
        break;
    case 4:
        func_001F9480(obj, 0, hasId, v0);
        func_001F9480(obj, 1, hasId, v1);
        func_001F9480(obj, 2, hasId, v2);
        func_001F9480(obj, 3, hasId, v3);
        break;
    default:
        break;
    }
    if (v4 > 0) {
        *(s32 *)(obj + 0xAE4) = v4;
        *(s32 *)(obj + 0xAE0) = amount;
    }
    if (v5 > 0) {
        *(s32 *)(obj + 0xAEC) = v5;
        *(s32 *)(obj + 0xAE8) = amount;
    }
    gauge = BtlMember_GetActiveGauge(obj);
    *(s32 *)(gauge + id * 4 + 0x30) += 1;
    return BtlMember_SubBlast(obj, func_00241C70(obj, id));
}
