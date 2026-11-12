#include "common.h"

extern u8 *D_00387848;
extern u8 *D_003876A0;
extern f32 D_00384EE4;

extern void func_00208DE8();
extern void func_00129C28(void *dst, void *src);
extern s32 func_0020A440(s32 arg0);
extern void func_001E7070(void *p);
extern s32 func_00207EC0(s32 arg0);
extern s32 func_001E70B0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 f12, void *arg6, void *arg7, s32 arg8);
extern void func_001E7208(void *arg0, s32 arg1);
extern s32 EftChain2_Create(void *p);
extern void EftChain2_SetType(s32 h, s32 t);
extern s32 EftMod1CB_Create(void *p);
extern void EftMod1CB_SetType(s32 h, s32 t);
extern s32 EftPtcl3_Create(void *p);
extern void EftPtcl3_SetTexture(s32 h, void *tex, s32 a2, s32 slot);
extern void EftPtcl3_SetType(s32 h, s32 t);
extern void EftPtcl3_SetFlag80(s32 h, s32 v);
extern void EftPtcl3_SetStartDelay(s32 h, f32 f);
extern void func_001AA4B0(u8 *p);
extern s32 func_001CC978(void *p);
extern void func_001CCD10(s32 h, s32 v);
extern s32 EftQuad_Create(void *p);
extern void func_0018E428(s32 h, void *p, s32 a2, s32 slot);
extern void func_0018E590(s32 h, s32 v);
extern void func_0018E480(s32 h, s32 v);
extern void func_0018E5E0(s32 h, s32 v);
extern void Vec3_Scale(u8 *out, u8 *a, f32 s);
extern void func_001F3738(u8 *p, s32 v);

void func_001AAA90(u8 *self, u8 *src) {
    u8 *tbl;
    u8 *obj;
    u8 *pos;
    u8 *vecA;
    u8 *vecB;
    u8 *g;
    u8 *blk;
    u8 *e;
    u8 B[0x50];
    u8 W[0x50];
    u8 tmp[0x50];
    u8 loc[0x10];
    u32 type;
    u32 fl;
    s32 slot;
    s32 i;
    s32 h;
    s32 a;
    s32 b;
    f32 sc;
    f32 f;

    tbl = D_00387848 + 8;
    obj = *(u8 **)(self + 0x38);
    __builtin_memset(obj, 0, 0xF0);
    pos = obj + 0x80;
    vecA = obj + 0x90;
    vecB = obj + 0xB0;
    for (i = 0; i < 8; i++) {
        *(u64 *)(obj + 0x40 + i * 8) = *(u64 *)(src + i * 8);
    }
    *(u16 *)(obj + 0x50) = *(u16 *)(src + 0x12);
    func_00208DE8(*(s16 *)(src + 0x12), pos, *(s16 *)(src + 0x14));
    func_00208DE8(*(s16 *)(src + 0x12), vecA, *(s16 *)(src + 0x14));
    func_00208DE8(*(s16 *)(src + 0x12), obj + 0xA0, 0x11);
    func_00129C28(vecB, src);
    *(f32 *)(obj + 0x2C) = *(f32 *)(src + 0x28);
    *(f32 *)(obj + 0x38) = *(f32 *)(src + 0x2C);
    *(s32 *)(obj + 0xC) = *(s16 *)(src + 0x1C);
    *(s32 *)(obj + 0x14) = 0;
    *(s32 *)(obj + 0x10) = src[0x1B];
    *(s32 *)(obj + 0x8) = 0;
    if (func_0020A440(*(s16 *)(obj + 0x52)) != 0) {
        *(u32 *)obj |= 4;
    }
    func_001E7070(obj + 0xE8);
    type = obj[0x5A];
    if ((s32)type < 14 && (s32)type >= 7) {
        *(u32 *)obj |= 0x80;
    }
    switch (type) {
    case 1:
    case 2:
    case 3:
        *(s32 *)(obj + 0x18) = type - 1;
        *(u32 *)(obj + 4) |= 1;
        break;
    case 4:
    case 5:
    case 6:
        *(s32 *)(obj + 0x1C) = type - 3;
        *(u32 *)(obj + 4) |= 2;
        break;
    case 7:
        break;
    case 8:
    case 9:
    case 10:
        *(s32 *)(obj + 0x18) = type - 8;
        *(u32 *)(obj + 4) |= 1;
        break;
    case 11:
    case 12:
    case 13:
        *(s32 *)(obj + 0x1C) = type - 10;
        *(u32 *)(obj + 4) |= 2;
        break;
    default:
        break;
    }

    if (*(u64 *)(D_003876A0 + 0x4D8) & 2) {
        if (func_00207EC0(*(s16 *)(obj + 0x52)) == 0x42) {
            if ((*(u32 *)obj & 0x80) != 0) {
                *(u32 *)(obj + 4) &= ~1u;
            }
        }
    }

    slot = *(s32 *)(obj + 0x10);
    if ((*(u32 *)obj & 0x80) == 0) {
        *(f32 *)(obj + 0x24) = 5.0f;

        /* EftMod1CB */
        blk = B;
        *(s32 *)(blk + 0) = *(s16 *)(obj + 0x52);
        *(s32 *)(blk + 4) = *(s32 *)(obj + 0x10);
        g = *(u8 **)tbl;
        *(f32 *)(blk + 8) = *(f32 *)(g + 0xA0);
        g = *(u8 **)tbl;
        *(f32 *)(blk + 0xC) = *(f32 *)(g + 0xA4) * *(f32 *)(obj + 0x2C);
        __builtin_memset(blk + 0x10, 0, 0x10);
        __builtin_memset(blk + 0x20, 0, 0x10);
        *(s32 *)(blk + 0x30) = 0;
        *(s32 *)(blk + 0x34) = 0;
        *(s32 *)(blk + 0x38) = *(s32 *)(tbl + 0x368);
        *(s32 *)(blk + 0x3C) = *(s32 *)(tbl + 0x36C) + (*(s32 *)(obj + 0x10) << 7);
        func_00129C28(blk + 0x10, vecA);
        func_00129C28(blk + 0x20, vecB);
        h = EftMod1CB_Create(blk);
        *(s32 *)(obj + 0xD0) = h;
        EftMod1CB_SetType(h, 0);

        /* EftPtcl3 */
        g = *(u8 **)tbl;
        f = *(f32 *)(obj + 0x2C) * *(f32 *)(g + 0xC0);
        blk = W;
        *(f32 *)(blk + 0) = *(f32 *)(g + 0xA0);
        *(f32 *)(blk + 4) = f;
        __builtin_memset(blk + 0x10, 0, 0x10);
        __builtin_memset(blk + 0x20, 0, 0x10);
        *(s32 *)(blk + 0x30) = 0;
        *(u8 **)(blk + 0x34) = tbl + 0x570;
        *(s32 *)(blk + 0x38) = *(s32 *)(tbl + 0x9C8);
        *(s32 *)(blk + 0x3C) = *(s32 *)(tbl + 0x9D8) + *(s32 *)(obj + 0x10) * 80;
        *(s32 *)(blk + 0x40) = *(s16 *)(obj + 0x52);
        __builtin_memcpy(tmp, blk, 0x50);
        func_00129C28(tmp + 0x10, vecA);
        func_00129C28(tmp + 0x20, vecB);
        h = EftPtcl3_Create(tmp);
        *(s32 *)(obj + 0xE0) = h;
        EftPtcl3_SetTexture(h, tbl + 0x570, 0, *(s32 *)(obj + 0x10));
        EftPtcl3_SetType(*(s32 *)(obj + 0xE0), 0);
        func_001AA4B0(self);

        /* func_001CC978 */
        f = *(f32 *)(obj + 0x2C);
        blk = B;
        *(s32 *)(blk + 0) = *(s16 *)(obj + 0x52);
        *(s32 *)(blk + 4) = 0;
        *(f32 *)(blk + 8) = *(f32 *)(*(u8 **)tbl + 0xD0);
        *(f32 *)(blk + 0xC) = f;
        __builtin_memset(blk + 0x10, 0, 0x10);
        __builtin_memset(blk + 0x20, 0, 0x10);
        *(u8 **)(blk + 0x30) = tbl + 0xD68;
        *(s32 *)(blk + 0x34) = *(s32 *)(tbl + 0xE78);
        *(s32 *)(blk + 0x38) = *(s32 *)(tbl + 0xE7C) + (*(s32 *)(obj + 0x10) << 4);
        func_00129C28(blk + 0x10, vecA);
        func_00129C28(blk + 0x20, vecB);
        h = func_001CC978(blk);
        *(s32 *)(obj + 0xE4) = h;
        func_001CCD10(h, 0);
    } else {
        i = *(s32 *)(obj + 8);
        f = *(f32 *)(obj + 0x2C) * *(f32 *)(*(u8 **)tbl + 0xAC);
        if (f <= 0.0f) {
            f = *(f32 *)(obj + 0x2C) * 20.0f;
        }
        e = obj + i * 4 + 0xE8;
        func_001E70B0(e, *(s32 *)(tbl + (7 * i + *(s32 *)(obj + 0x10)) * 4 + 0xA08), 0, 0, 0, f,
                      vecA, tbl + i * 536 + 0xA30, *(s16 *)(obj + 0x52));
        func_001E7208(e, 0);
        sc = *(f32 *)(obj + 0x2C);
        f = sc * *(f32 *)(*(u8 **)tbl + 0xB0);
        if (f <= 0.0f) {
            f = sc * D_00384EE4;
        }
        blk = B;
        *(s32 *)(blk + 0) = *(s16 *)(obj + 0x52);
        *(s32 *)(blk + 4) = *(s32 *)(obj + 0x10);
        *(f32 *)(blk + 8) = 0.0f;
        *(f32 *)(blk + 0xC) = f;
        __builtin_memset(blk + 0x10, 0, 0x10);
        __builtin_memset(blk + 0x20, 0, 0x10);
        *(s32 *)(blk + 0x30) = 0;
        *(u8 **)(blk + 0x34) = tbl + 0xC48;
        *(s32 *)(blk + 0x38) = *(s32 *)(tbl + 0xD58);
        *(s32 *)(blk + 0x3C) = *(s32 *)(tbl + 0xD5C) + (*(s32 *)(obj + 0x10) << 6);
        func_00129C28(blk + 0x20, vecB);
        func_00129C28(blk + 0x10, vecA);
        h = EftChain2_Create(blk);
        *(s32 *)(obj + 0xEC) = h;
        EftChain2_SetType(h, 0);
    }

    if ((*(u32 *)(obj + 4) & 1) != 0) {
        i = *(s32 *)(obj + 0x18);
        slot = *(s32 *)(obj + 0x10);
        f = *(f32 *)(obj + 0x2C);
        a = *(s32 *)(tbl + i * 4 + 0x538);
        b = *(s32 *)(tbl + i * 4 + 0x544) + (slot << 6);
        if ((*(u32 *)obj & 0x80) != 0) {
            a = *(s32 *)(tbl + i * 4 + 0x550);
            b = *(s32 *)(tbl + i * 4 + 0x550 + 0xC) + (slot << 6);
        }
        blk = B;
        *(s32 *)(blk + 0) = a;
        *(s32 *)(blk + 4) = b;
        *(u8 **)(blk + 8) = tbl + *(s32 *)(obj + 0x18) * 152 + 0x378;
        __builtin_memset(blk + 0x10, 0, 0x10);
        __builtin_memset(blk + 0x20, 0, 0x10);
        *(f32 *)(blk + 0x30) = f;
        *(s32 *)(blk + 0x34) = 0;
        *(s32 *)(blk + 0x38) = *(s16 *)(obj + 0x52);
        func_00129C28(blk + 0x20, vecB);
        func_00129C28(blk + 0x10, vecA);
        h = EftQuad_Create(blk);
        *(s32 *)(obj + 0xD8) = h;
        func_0018E428(h, tbl + *(s32 *)(obj + 0x18) * 152 + 0x378, 0, *(s32 *)(obj + 0x10));
        h = *(s32 *)(obj + 0xD8);
        if ((*(u32 *)obj & 0x80) == 0) {
            func_0018E590(h, 1);
            h = *(s32 *)(obj + 0xD8);
        }
        func_0018E480(h, 3);
        func_0018E5E0(*(s32 *)(obj + 0xD8), 0);
    }

    if ((*(u32 *)(obj + 4) & 2) != 0) {
        i = *(s32 *)(obj + 0x1C);
        slot = *(s32 *)(obj + 0x10);
        a = *(s32 *)(tbl + i * 4 + 0x9C8);
        b = *(s32 *)(tbl + i * 4 + 0x9D8) + slot * 80;
        f = *(f32 *)(obj + 0x2C);
        if ((*(u32 *)obj & 0x80) != 0) {
            a = *(s32 *)(tbl + i * 4 + 0x9E8);
            b = *(s32 *)(tbl + i * 4 + 0x9F8) + slot * 80;
        }
        blk = W;
        *(s32 *)(blk + 0) = 0;
        *(f32 *)(blk + 4) = f;
        __builtin_memset(blk + 0x10, 0, 0x10);
        __builtin_memset(blk + 0x20, 0, 0x10);
        *(s32 *)(blk + 0x30) = 0;
        *(u8 **)(blk + 0x34) = tbl + *(s32 *)(obj + 0x1C) * 280 + 0x570;
        *(s32 *)(blk + 0x38) = a;
        *(s32 *)(blk + 0x3C) = b;
        *(s32 *)(blk + 0x40) = *(s16 *)(obj + 0x52);
        __builtin_memcpy(tmp, blk, 0x50);
        func_00129C28(tmp + 0x10, vecA);
        Vec3_Scale(loc, vecB, -1.0f);
        *(f32 *)(loc + 0xC) = 1.0f;
        func_00129C28(tmp + 0x20, loc);
        h = EftPtcl3_Create(tmp);
        *(s32 *)(obj + 0xDC) = h;
        EftPtcl3_SetTexture(h, tbl + *(s32 *)(obj + 0x1C) * 280 + 0x570, 0, *(s32 *)(obj + 0x10));
        if ((*(u32 *)obj & 0x80) == 0 && *(s32 *)(obj + 0x1C) != 3) {
            EftPtcl3_SetFlag80(*(s32 *)(obj + 0xDC), 1);
        }
        EftPtcl3_SetStartDelay(*(s32 *)(obj + 0xDC), 3.0f);
        EftPtcl3_SetType(*(s32 *)(obj + 0xDC), 0);
    }
    func_001F3738(self, 0x2000);
}
