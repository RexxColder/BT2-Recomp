#include "common.h"

extern f32 D_00385FCC;
extern f32 D_00385FD0;
extern f32 D_00385FD4;
extern f32 D_00385FD8;
extern f32 D_00385FDC;
extern f32 D_00385FE0;
extern f32 D_00385FE4;
extern f32 D_00385FE8;
extern f32 D_00385FEC;
extern f32 D_00385FF0;
extern f32 D_00385FF4;
extern f32 D_00385FF8;
extern f32 D_00385FFC;
extern f32 D_00386000;
extern f32 D_00386004;

void BtlAnim_SetBlend(u8 *arg0, f32 arg1);
s32 BtlObjXf_Update(u8 *arg0, f32 arg1);
s32 func_00218540(u8 *arg0, f32 arg1);
s32 func_00218560(u8 *arg0, f32 arg1);
s32 func_00212820();
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_0023FB58();
s32 func_00203888(u8 *arg0, s32 arg1, s32 arg2);
s32 func_0023F410(u8 *arg0);
void func_00203310();
void func_002113C0();
u8 *BtlChar_GetPos(u8 *arg0);
void func_0020D048(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_0020D240(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void sceVu0Normalize(f32 *arg0, u8 *arg1);
f32 sceVu0InnerProduct(f32 *arg0, f32 *arg1);
f32 func_001FA318(u8 *arg0);
s32 func_0023C798(u8 *arg0, s32 arg1);
s32 func_0023BDA8(u8 *arg0, s32 arg1);
s32 func_0023C710(u8 *arg0);

s32 func_00221A40(u8 *arg0, f32 farg) {
    f32 vecA[4];
    f32 vecB[4];
    s32 r;
    s32 s0;
    s32 s2;
    u8 *pos;
    f32 f0;

    if (*(s32 *)(arg0 + 0x8DC) & 1) {
        BtlAnim_SetBlend(arg0, D_00385FCC);
        return 0x21;
    }
    r = BtlObjXf_Update(arg0, farg);
    if (r >= 0xFD) {
        if (r >= 0x1A8 || r < 0x1A6) {
            return -1;
        }
        goto L_E98;
    }
    if (r >= 0xFB) {
        goto L_E28;
    }
    if (r >= 0xD4) {
        return -1;
    }
    if (r < 0xD2) {
        return -1;
    }

    /* AE0: r in [0xD2, 0xD4) */
    if (func_00218540(arg0, D_00385FD0) == 0) {
        goto L_C48;
    }
    if (!(D_00385FD4 < (f32)*(s32 *)(arg0 + 0x8CC))) {
        goto L_BCC;
    }
    if (func_00212820(arg0, 0x1F4) == 0) {
        goto L_BCC;
    }
    if (func_00211310(arg0, 1, 0x80000) != 0) {
        goto L_BCC;
    }
    if (func_00211310(arg0, 1, 0x4000) == 0) {
        goto L_B68;
    }
    func_00203888(arg0, func_0023FB58(arg0), 0);
    goto L_BAC;

L_B68:
    if (func_00211310(arg0, 1, 0x8000) == 0) {
        goto L_BCC;
    }
    func_00203888(arg0, func_0023FB58(arg0), 0);
    if (func_00211310(arg0, 0, 1) != 0) {
        return 0x2B;
    }
    goto L_BAC;

L_BAC:
    return (func_0023F410(arg0) & 0x1000) ? 0x27 : 0x29;

L_BCC:
    func_00203310(arg0, 0x1F4, 0);
    func_002113C0(arg0, 6, 0x10, 1);
    pos = BtlChar_GetPos(arg0);
    func_0020D048(pos, 100.0f, 1000.0f, 3.0f, D_00385FD8);
    pos = BtlChar_GetPos(arg0);
    func_0020D240(pos, 100.0f, 1000.0f, D_00385FDC, D_00385FE0);
    return 0xA8;

L_D34:
    func_00203310(arg0, 0x258, 0);
    func_002113C0(arg0, 6, 0x10, 1);
    pos = BtlChar_GetPos(arg0);
    func_0020D048(pos, 100.0f, 1000.0f, 3.0f, D_00385FE8);
    pos = BtlChar_GetPos(arg0);
    func_0020D240(pos, 100.0f, 1000.0f, D_00385FEC, D_00385FF0);
    return 0xA9;

L_E0C:
    return (func_00212820(arg0) == 0) ? 0xA9 : 0x9B;

L_C48:
    if (func_00218560(arg0, D_00385FD0) == 0) {
        goto L_DB0;
    }
    if (*(s32 *)(*(u8 **)(arg0 + 0x1530) + 0xED0) & 0x40) {
        goto L_E0C;
    }
    if (!(D_00385FE4 < (f32)*(s32 *)(arg0 + 0x8CC))) {
        goto L_D34;
    }
    if (func_00212820(arg0, 0x258) == 0) {
        goto L_D34;
    }
    if (func_00211310(arg0, 1, 0x80000) != 0) {
        goto L_D34;
    }
    if (func_00211310(arg0, 1, 0x4000) == 0) {
        goto L_CE0;
    }
    func_00203888(arg0, func_0023FB58(arg0), 0);
    return 0x2A;

L_CE0:
    if (func_00211310(arg0, 1, 0x8000) == 0) {
        goto L_D34;
    }
    func_00203888(arg0, func_0023FB58(arg0), 0);
    return (func_00211310(arg0, 0, 1) != 0) ? 0x2C : 0x2A;

L_DB0:
    if (func_00211310(arg0, 0, 8) == 0) {
        return -1;
    }
    pos = BtlChar_GetPos(arg0);
    sceVu0Normalize(vecA, pos);
    pos = BtlChar_GetPos(arg0);
    sceVu0Normalize(vecB, pos + 0x40);
    if (D_00385FF4 < sceVu0InnerProduct(vecA, vecB)) {
        goto L_E0C;
    }
    return -1;

L_E28:
    f0 = func_001FA318(arg0);
    if (!(D_00385FF8 < f0)) {
        goto L_E98;
    }
    s0 = func_0023C798(arg0, 3);
    if (s0 != -1) {
        BtlAnim_SetBlend(arg0, D_00385FFC);
        return s0;
    }
    s2 = func_0023BDA8(arg0, 0x420000);
    if (s2 == -1) {
        goto L_E98;
    }
    BtlAnim_SetBlend(arg0, D_00386000);
    return s2;

L_E98:
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_00386004);
    return func_0023C710(arg0);
}
