#include "common.h"

f32 func_00272FA8(void);
f32 func_00273000(void);
f32 func_00273048(void);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
s32 func_00212878(void);
s32 func_00212820(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x0020E6B8 (per-frame height/offset update of a character). The character record is at obj+0x1530 with the
 * horizontal velocity at +0x9A0 / +0x9A8 and the vertical values at +0x9A4; the record at +0xF40 gives a bound at +0x10.
 * The horizontal part is scaled down to the bound, the vertical part is raised toward the character height
 * (BtlCharApi_GetHeight of obj+0x1534) in two states, and all three are finally clamped to +-185. */
void func_0020E6B8(u8 *obj) {
    u8 *ch;
    u8 *bound;
    f32 len;
    f32 diff;
    f32 scale;
    f32 base;
    f32 h;
    f32 f2;

    ch = *(u8 **)(obj + 0x1530);
    len = __builtin_sqrtf(*(f32 *)(ch + 0x9A0) * *(f32 *)(ch + 0x9A0) +
                          *(f32 *)(ch + 0x9A8) * *(f32 *)(ch + 0x9A8));

    base = func_00272FA8();
    ch = *(u8 **)(obj + 0x1530);
    bound = *(u8 **)(ch + 0xF40);
    diff = base - *(f32 *)(bound + 0x10);

    if (diff < len) {
        scale = diff / len;
        *(f32 *)(ch + 0x9A0) = *(f32 *)(ch + 0x9A0) * scale;
        *(f32 *)(ch + 0x9A8) = *(f32 *)(ch + 0x9A8) * scale;
        func_002113C0((s32)obj, 0, 8, 1);
    } else {
        func_002113C0((s32)obj, 0, 8, 0);
    }

    if (func_00211310((s32)obj, 1, 0x100000) == 0) {
        base = func_00273000();
        h = BtlCharApi_GetHeight(*(s32 *)(obj + 0x1534));
        base = base + h * 0.5f;
        ch = *(u8 **)(obj + 0x1530);
        f2 = *(f32 *)(ch + 0x9A4);
        if (f2 < base) {
            *(f32 *)(ch + 0x9A4) = base;
            func_002113C0((s32)obj, 0, 0x10, 1);
        } else {
            func_002113C0((s32)obj, 0, 0x10, 0);
        }
    }

    if (BtlMember_IsHealthEmpty_2127F8((s32)obj) == 0) {
        base = func_00273048();
        h = BtlCharApi_GetHeight(*(s32 *)(obj + 0x1534));
        base = base + h * 0.5f;
        ch = *(u8 **)(obj + 0x1530);
        f2 = *(f32 *)(ch + 0x9A4);
        if (base < f2) {
            *(f32 *)(ch + 0x9A4) = base;
            func_002113C0((s32)obj, 0, 0x20, 1);
        } else {
            func_002113C0((s32)obj, 0, 0x20, 0);
        }
    }

    func_002113C0((s32)obj, 0, 0x40, 0);

    if (func_00212878() != 0) {
        if (func_00212820((s32)obj) != 0) {
            if (func_00211310((s32)obj, 1, 0x2000000) == 0 && func_00211310((s32)obj, 0, 0x8000) == 0) {
                ch = *(u8 **)(obj + 0x1530);
                if (-10.0f < *(f32 *)(ch + 0x9A4)) {
                    *(f32 *)(ch + 0x9A4) = -10.0f;
                    func_002113C0((s32)obj, 0, 0x40, 1);
                }
            }
        }

        if (func_00211310((s32)obj, 0, 0x200000) != 0) {
            ch = *(u8 **)(obj + 0x1530);
            if (*(f32 *)(ch + 0x9A0) < -185.0f) {
                *(f32 *)(ch + 0x9A0) = -185.0f;
            }
            ch = *(u8 **)(obj + 0x1530);
            if (*(f32 *)(ch + 0x9A8) < -185.0f) {
                *(f32 *)(ch + 0x9A8) = -185.0f;
            }
            ch = *(u8 **)(obj + 0x1530);
            if (185.0f < *(f32 *)(ch + 0x9A0)) {
                *(f32 *)(ch + 0x9A0) = 185.0f;
            }
            ch = *(u8 **)(obj + 0x1530);
            if (185.0f < *(f32 *)(ch + 0x9A8)) {
                *(f32 *)(ch + 0x9A8) = 185.0f;
            }
        }
    }
}
