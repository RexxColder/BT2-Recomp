#include "common.h"

extern f32 D_0038630C;
extern f32 D_00386310;
extern f32 D_00386314;
extern f32 D_00386318;
extern f32 D_0038631C;
extern f32 D_00386320;
extern f32 D_00386324;
extern f32 D_00386328;
extern f32 D_0038632C;
extern f32 D_00386330;
extern f32 D_00386334;
extern f32 D_00386338;
extern f32 D_0038633C;
extern f32 D_00386340;

s32 func_00211310(void *a0, s32 a1, s32 a2);
f32 func_00240D50(void *a0, s32 a1);
s32 BtlObjXf_Update(void *a0);
s32 func_001FA0A0(void *a0, s32 a1, s32 a2);
void func_002113C0(void *a0, s32 a1, s32 a2, s32 a3);
void func_00206958(void *a0, s64 a1);
f32 func_001FA318(void *a0);
s32 BtlPad_Test48(void *a0, s32 a1);
void func_001F9D78(void *a0, s32 a1);
void BtlAnim_SetBlend(void *a0, f32 f12);
void *BtlChar_GetPos(void *a0);
f32 sinf(f32 x);
f32 cosf(f32 x);
s32 func_001FA2E0(void *a0);
s32 func_00240398(void *a0);
void func_00203888(void *a0, s32 a1, s32 a2);
void func_001F9FB0(void *a0, s32 a1);
s32 func_00217BD0(void *a0);
void func_00215E88(void *a0, s32 a1, f32 f12);
void func_00216208(void *a0, f32 f12, f32 f13);
void func_00216678(void *a0);
void func_0020D7E8(void *a0, f32 f12, f32 f13);
void func_00215068(void *a0, s32 a1, s32 a2, f32 f12, f32 f13);
f32 func_00240ED8(void *a0, s32 a1);
f32 func_00240F18(void *a0, s32 a1);
void func_00215550(void *a0, s32 a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18);
f32 BtlOpp_GetPitchAdjusted(void *a0);
void func_002181F0(void *a0, f32 f12);

void func_00227460(u8 *arg0) {
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 t;
    f32 f18v;
    s32 st;
    s32 a1;
    u8 *pos;

    f23 = D_0038630C;
    a1 = (func_00211310(arg0, 0, 0x100) != 0) ? 5 : 4;
    f21 = func_00240D50(arg0, a1);
    f22 = f21;
    st = BtlObjXf_Update(arg0);

    if (st == 0x93 || st == 0x96 || st == 0x90) {
        /* G1 */
        func_001FA0A0(arg0, BtlObjXf_Update(arg0) + 1, 0);
        func_002113C0(arg0, 5, 0x400, 1);
        func_00206958(arg0, 0x1000);
    } else if (st == 0x91 || st == 0x94 || st == 0x97) {
        /* G2 */
        func_001FA0A0(arg0, BtlObjXf_Update(arg0) + 1, 0);
        *(f32 *)(arg0 + 0xA1C) = func_001FA318(arg0);
        func_002113C0(arg0, 5, 0x400, 1);
        if (BtlPad_Test48(arg0, 1) == 0) {
            func_001F9D78(arg0, BtlObjXf_Update(arg0) + 1);
        }
        func_00206958(arg0, 0x1000);
    } else if (st == 0x92) {
        /* G3 */
        if (func_001FA0A0(arg0, 0x19, 0) != 0) {
            BtlAnim_SetBlend(arg0, D_00386310);
        }
        if (func_00211310(arg0, 0, 1) != 0 && (*(s32 *)(arg0 + 0x8DC) & 1)) {
            *(f32 *)(arg0 + 0xA00) = *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0x20);
            *(f32 *)(arg0 + 0xA04) = *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0x24);
            t = *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0x28);
        } else {
            pos = BtlChar_GetPos(arg0);
            t = sinf(*(f32 *)(pos + 0xB4));
            *(s32 *)(arg0 + 0xA04) = 0;
            *(f32 *)(arg0 + 0xA00) = t;
            pos = BtlChar_GetPos(arg0);
            t = cosf(*(f32 *)(pos + 0xB4));
        }
        *(s32 *)(arg0 + 0xA0C) = 0;
        *(f32 *)(arg0 + 0xA08) = t;
        if (func_001FA2E0(arg0) != 0) {
            func_00203888(arg0, func_00240398(arg0), 0);
        }
        func_00206958(arg0, 0x1000);
    } else if (st == 0x95) {
        /* G4: sin/cos of angle + D_00386318 */
        if (func_001FA0A0(arg0, 0x19, 0) != 0) {
            BtlAnim_SetBlend(arg0, D_00386314);
        }
        f20 = D_00386318;
        pos = BtlChar_GetPos(arg0);
        t = sinf(*(f32 *)(pos + 0xB4) + f20);
        *(s32 *)(arg0 + 0xA04) = 0;
        *(f32 *)(arg0 + 0xA00) = t;
        pos = BtlChar_GetPos(arg0);
        t = cosf(*(f32 *)(pos + 0xB4) + f20);
        *(s32 *)(arg0 + 0xA0C) = 0;
        *(f32 *)(arg0 + 0xA08) = t;
        if (func_001FA2E0(arg0) != 0) {
            func_00203888(arg0, func_00240398(arg0), 0);
        }
        func_00206958(arg0, 0x1000);
    } else if (st == 0x98) {
        /* G5: sin/cos of angle - D_00386320 */
        if (func_001FA0A0(arg0, 0x19, 0) != 0) {
            BtlAnim_SetBlend(arg0, D_0038631C);
        }
        f20 = D_00386320;
        pos = BtlChar_GetPos(arg0);
        t = sinf(*(f32 *)(pos + 0xB4) - f20);
        *(s32 *)(arg0 + 0xA04) = 0;
        *(f32 *)(arg0 + 0xA00) = t;
        pos = BtlChar_GetPos(arg0);
        t = cosf(*(f32 *)(pos + 0xB4) - f20);
        *(s32 *)(arg0 + 0xA0C) = 0;
        *(f32 *)(arg0 + 0xA08) = t;
        if (func_001FA2E0(arg0) != 0) {
            func_00203888(arg0, func_00240398(arg0), 0);
        }
        func_00206958(arg0, 0x1000);
    } else if (st == 0x19) {
        /* G6 */
        func_001F9FB0(arg0, 0);
        f21 = 0.0f;
        f23 = D_00386324;
        if (func_00217BD0(arg0) != 0) {
            pos = BtlChar_GetPos(arg0);
            *(f32 *)(pos + 0xC0) = f21;
        }
    }

    /* common tail (every case above falls here) */
    if (*(s32 *)(arg0 + 0x8DC) & 1) {
        if (func_00211310(arg0, 0, 1) != 0) {
            f20 = func_00240ED8(arg0, 0);
            f18v = func_00240F18(arg0, 0);
            func_00215550(arg0, 1, f22, f20, 0.0f, f18v, 0.0f, D_00386328, D_0038632C);
        } else {
            func_00215068(arg0, 5, 0xC, D_00386330, D_00386334);
        }
    } else {
        func_00215068(arg0, 5, 0xC, D_00386338, D_0038633C);
    }
    func_00215E88(arg0, 3, D_00386340);
    func_00216208(arg0, f21, f23);
    func_00216678(arg0);
    if (*(s32 *)(arg0 + 0x8DC) & 1) {
        func_002113C0(arg0, 9, 0x200, 1);
    }
    func_0020D7E8(arg0, 20.0f, 50.0f);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xF, 0x40, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
    if (func_00211310(arg0, 0, 1) == 0) {
        return;
    }
    if (!(*(s32 *)(arg0 + 0x8DC) & 1)) {
        return;
    }

    f21 = 0.0f;
    st = BtlObjXf_Update(arg0);
    if (st == 0x19) {
        f21 = 1.0f - func_001FA318(arg0);
    } else if (st >= 0x19 && st < 0x93 && st >= 0x90) {
        f21 = 1.0f;
    }
    f20 = BtlOpp_GetPitchAdjusted(arg0);
    if (0.0f < f20) {
        f20 = f20 * 0.5f;
    }
    pos = BtlChar_GetPos(arg0);
    *(f32 *)(pos + 0xD4) = f20 * f21;
    func_002181F0(arg0, 10.0f);
}
