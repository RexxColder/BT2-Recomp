#include "common.h"

extern u8 D_0036E340[] __attribute__((section(".data")));

s32 func_001F3758(s32 arg0);
void func_002088F0(s32 arg0, s32 arg1);
void Mtx_StoreIdentity(s32 arg0);
void Mtx_RotateY(s32 dst, s32 src, f32 angle);
void Vec3_Sub(s32 dst, s32 a, s32 b);
void func_00129C50(void *a0, void *a1, void *a2);
s32 Vec3_Normalize(s32 arg0, s32 arg1);
s32 EftGeyser_Create(u8 *a0, s32 a1);
s32 func_0019D6B8(s32 arg0, s32 arg1);

s32 func_0015DAE0(u8 *obj, s32 idx) {
    u8 geyser[0x90];   /* EftGeyser parameter block; vec scratch lives at +0x60 */
    u8 stage[0x90];    /* staging block; the matrix is built at +0x10 */
    u8 *probe;
    u8 *cfg;
    u8 *sub;
    u8 *ptr2;
    s32 v42;
    s32 eft;
    u8 *mtx;
    u8 *vec;

    probe = (u8 *)func_001F3758((s32)obj);
    cfg = *(u8 **)(probe + 0x38);
    sub = *(u8 **)(obj + 0x38);
    ptr2 = *(u8 **)(sub + 0xC0);
    v42 = *(s32 *)ptr2;

    *(s32 *)(stage + 0x00) = *(s32 *)(cfg + 0x1E80);
    *(f32 *)(stage + 0x04) = 0.0f;
    *(u8 **)(stage + 0x08) = ptr2;
    *(u8 **)(stage + 0x0C) = cfg;
    *(u8 **)(stage + 0x10) = sub + 0x870;
    __builtin_memcpy(stage + 0x14, D_0036E340, 0x1C);
    *(f32 *)(stage + 0x30) = 128.0f;
    *(f32 *)(stage + 0x34) = 128.0f;
    *(f32 *)(stage + 0x38) = 128.0f;
    *(f32 *)(stage + 0x3C) = 128.0f;
    __builtin_memcpy(stage + 0x40, sub + 0x90, 8);
    __builtin_memcpy(stage + 0x48, sub + 0x98, 8);
    __builtin_memcpy(stage + 0x50, sub + 0xB0, 8);
    __builtin_memcpy(stage + 0x58, sub + 0xB8, 8);
    __builtin_memset(stage + 0x60, 0, 16);
    *(f32 *)(stage + 0x70) = *(f32 *)(sub + 0x18);
    *(f32 *)(stage + 0x74) = *(f32 *)(sub + 0x20);
    *(s32 *)(stage + 0x78) = 0;
    *(s32 *)(stage + 0x7C) = 0;
    *(s32 *)(stage + 0x80) = v42;

    __builtin_memcpy(geyser, stage, 0x90);

    mtx = stage + 0x10;
    Mtx_StoreIdentity((s32)mtx);
    func_002088F0(v42, (s32)stage);
    Mtx_RotateY((s32)mtx, (s32)mtx, -*(f32 *)(stage + 0x04));

    vec = geyser + 0x60;
    Vec3_Sub((s32)vec, (s32)(sub + 0x60), (s32)(sub + 0x70));
    func_00129C50(vec, mtx, vec);
    Vec3_Normalize((s32)vec, (s32)vec);

    eft = EftGeyser_Create(geyser, (s32)vec);
    *(s32 *)(sub + 0xAC0 + 4 * idx) = eft;
    return func_0019D6B8(eft, 4);
}
