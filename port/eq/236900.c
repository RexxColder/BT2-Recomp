#include "common.h"

extern f32 D_003869F4;
extern f32 D_003869F8;
extern f32 D_003869FC;
extern f32 D_00386A00;
extern f32 D_00386A04;
extern f32 D_00386A08;
extern f32 D_00386A0C;
extern f32 D_00386A10;
extern f32 D_00386A14;
extern u8 D_002C3630 __attribute__((section(".data")));

s32 func_00212320(u8 *obj);
s32 BtlObjXf_Update(u8 *obj);
s32 func_001FA0A0(u8 *obj, s32 a1, s32 a2);
s32 func_001FA2E0(u8 *obj);
void func_00230C48(u8 *obj);
void func_00230BB0(u8 *obj, s32 a1);
void func_00230C60(u8 *obj, s32 a1);
void func_002113C0(u8 *obj, s32 a1, s32 a2, s32 a3);
void BtlChar_Vibrate(u8 *obj, f32 f12, f32 f13);
void func_001FCD80(u8 *obj);
void func_001FA110(u8 *obj, s32 a1);
void BtlChar_SetSmallVibration(u8 *obj, f32 f12);
f32 func_00241218(u8 *obj, s32 a1);
void func_001F9D78(u8 *obj, s32 a1);
s32 func_00211310(u8 *obj, s32 a1, s32 a2);
void func_001F9FB0(u8 *obj, s32 a1);
f32 func_00241B90(u8 *obj, s32 a1);
void func_00215B80(u8 *obj, f32 f12, f32 f13, f32 f14);
void func_00215E88(u8 *obj, s32 a1, f32 f12);
void func_00216208(u8 *obj, f32 f12, f32 f13);
void func_00215068(u8 *obj, s32 a1, s32 a2, f32 f12, f32 f13);
void func_00216678(u8 *obj);
s32 func_002411E0(u8 *obj, s32 a1);
void func_00206958(u8 *obj, s32 a1);
f32 func_001FA318(u8 *obj);
u8 *BtlChar_GetPos(u8 *obj);
void func_002181F0(u8 *obj, f32 f12);
f32 BtlCharApi_GetHeight(s32 a0);
void func_001FC3B0(f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17,
                   u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, u8 *t1, u8 *t2, s32 t3,
                   s32 s8, s32 s9, s32 s10, s32 s11, s32 s12);

void func_00236900(u8 *obj) {
    s32 *counter = (s32 *)(obj + 0x8C4);
    s32 hasTail = 0;
    s32 hasPos = 0;
    s32 st;
    s32 id;
    f32 scale;
    f32 pad;
    f32 ratio;
    f32 f0;
    f32 height;
    f32 posX;
    f32 posY;
    u8 *pos;

    st = func_00212320(obj);
    id = BtlObjXf_Update(obj);
    switch (id) {
    case 284: case 318: case 352:
        func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0);
        if (func_001FA2E0(obj) != 0) {
            func_00230BB0(obj, st);
        }
        func_00230C60(obj, 0);
        func_002113C0(obj, 9, 4, 1);
        break;
    case 285: case 319: case 353:
        func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0);
        func_00230C60(obj, 0);
        func_002113C0(obj, 9, 4, 1);
        break;
    case 386:
        func_001FA0A0(obj, 0x160, 0);
        if (func_001FA2E0(obj) != 0) {
            func_00230C48(obj);
        }
        func_00230C60(obj, 0);
        func_002113C0(obj, 9, 4, 1);
        break;
    case 286: case 320: case 354:
        func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0);
        if (func_001FA2E0(obj) != 0) {
            BtlChar_Vibrate(obj, D_003869F4, D_003869F8);
            func_002113C0(obj, 0xE, 0x200, 1);
            func_001FCD80(obj);
        }
        func_002113C0(obj, 1, 0x2000, 1);
        hasTail = 1;
        hasPos = 1;
        break;
    case 287: case 321: case 355:
        func_001FA110(obj, 0);
        func_002113C0(obj, 3, 0x400, 1);
        hasTail = 1;
        func_002113C0(obj, 1, 0x2000, 1);
        hasPos = 1;
        BtlChar_SetSmallVibration(obj, D_003869FC);
        *counter = *counter + 1;
        scale = (f32)*counter;
        f0 = func_00241218(obj, st) * 30.0f;
        if (f0 < scale) {
            func_001F9D78(obj, BtlObjXf_Update(obj) + 3);
        }
        if (func_00211310(obj, 0, 1) == 0) {
            func_001F9D78(obj, BtlObjXf_Update(obj) + 3);
        }
        break;
    case 290: case 324: case 358:
        func_001F9FB0(obj, 0);
        break;
    default:
        break;
    }

    if (hasTail != 0) {
        scale = func_00241B90(obj, st);
        pad = D_00386A04;
        func_00215B80(obj, D_00386A00, D_00386A00, pad);
        func_00215E88(obj, 3, pad);
        func_00216208(obj, scale, D_00386A08);
    } else {
        scale = D_00386A0C;
        func_00215068(obj, 5, 0xD, D_00386A10, scale);
        func_00215E88(obj, 7, scale);
        func_00216208(obj, 0.0f, D_00386A14);
    }
    func_00216678(obj);
    func_002113C0(obj, 0xD, 8, 1);
    func_002113C0(obj, 0xD, 0x10, 1);
    func_002113C0(obj, 0xD, 1, 1);
    func_002113C0(obj, 1, 0x40, 1);
    func_002113C0(obj, 1, 0x800000, 1);
    if ((func_002411E0(obj, st) & 0x10) == 0) {
        func_00206958(obj, 0x8000);
    }

    if (func_00211310(obj, 0, 1) != 0) {
        ratio = 0.0f;
        id = BtlObjXf_Update(obj);
        switch (id) {
        case 286: case 320: case 354:
            ratio = func_001FA318(obj);
            break;
        case 287: case 321: case 355:
            ratio = 1.0f;
            break;
        case 290: case 324: case 358:
            ratio = 1.0f - func_001FA318(obj);
            break;
        default:
            break;
        }
        pos = BtlChar_GetPos(obj);
        posX = *(f32 *)(pos + 0xB0);
        pos = BtlChar_GetPos(obj);
        *(f32 *)(pos + 0xD4) = posX * ratio;
        func_002181F0(obj, 10.0f);
    }

    if (hasPos != 0) {
        pos = BtlChar_GetPos(obj);
        posY = *(f32 *)(pos + 0xB4);
        pos = BtlChar_GetPos(obj);
        posX = *(f32 *)(pos + 0xB0) - 0.5f;
        height = BtlCharApi_GetHeight(*(s32 *)(obj + 0x1534));
        func_001FC3B0(posY, 0.0f, posX, 0.0f, height * 3.0f, 0.0f,
                      obj, &D_002C3630, &D_002C3630, &D_002C3630, &D_002C3630, &D_002C3630, &D_002C3630, 0,
                      0, 2, 2, 1, 0x15);
    }
}
