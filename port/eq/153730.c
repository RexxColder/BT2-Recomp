#include "common.h"

extern f32 D_0038467C;
extern f32 D_00384680;
extern f32 D_00384684;
extern f32 D_00384688;

s32 func_001F3758(void *a0);
s32 rand(void);
void Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Mtx_StoreIdentity(s32 arg0);
void Mtx_RotateX(s32 arg0, s32 arg1, f32 farg0);
void Mtx_RotateY(s32 arg0, s32 arg1, f32 farg0);
void func_00129C50(s32 arg0, s32 arg1, s32 arg2);
f32 Mathf_Asin(f32 farg0);
s32 func_00191600(s32 arg0);
s32 func_001919C8(s32 arg0);

/* Spawns five blast objects around the owner: each picks a random tilt (two rand() draws), rotates an
 * identity matrix by the tilt and the loop index, rotates the owner's direction by its asin/atan2 pitch
 * and yaw, and builds a 48-byte descriptor for func_00191600. The returned object pointers are stored
 * in the table at arg0.+0xAA4. */
s32 func_00153730(s32 a1) {
    u8 sp[0x140];
    s32 base = *(s32 *)(a1 + 0x38);
    s32 v37 = *(s32 *)(func_001F3758((void *)a1) + 0x38);
    s32 s5 = *(s32 *)(base + 0xA0);
    s32 s7 = base + 0x60;
    s32 fp = base + 0x850;
    s32 s4 = base + 0xAA4;
    s32 vec = (s32)(sp + 0x40);
    s32 mat = (s32)(sp + 0);
    s32 desc = (s32)(sp + 0x50);
    s32 i = 0;
    s32 r1;
    s32 r2;
    s32 result = 0;
    f32 asinv;
    f32 atanv;

    do {
        Vec4_Set(vec, 0.0f, 0.0f, 1.0f, 1.0f);
        Mtx_StoreIdentity(mat);
        r1 = rand();
        r2 = rand();
        Mtx_RotateX(mat, mat,
                    (((f32)r1 / D_0038467C - (f32)r2 / D_0038467C) * D_00384680) * D_00384684);
        Mtx_RotateY(mat, mat, ((f32)(i - 2) * D_00384680) * D_00384688);
        func_00129C50(vec, mat, vec);

        asinv = Mathf_Asin(-*(f32 *)(base + 0x24));
        atanv = __builtin_atan2f(*(f32 *)(base + 0x20), *(f32 *)(base + 0x28));
        Mtx_StoreIdentity(mat);
        Mtx_RotateX(mat, mat, asinv);
        Mtx_RotateY(mat, mat, atanv);
        func_00129C50(vec, mat, vec);

        *(s32 *)(sp + 0x98) = 5;
        *(s32 *)(sp + 0x9C) = 2;
        *(s32 *)(sp + 0xA0) = 1;
        *(f32 *)(sp + 0xA4) = 0.0f;
        *(s32 *)(sp + 0x80) = s5;
        *(s32 *)(sp + 0x84) = v37;
        *(s32 *)(sp + 0x88) = fp;
        *(s32 *)(sp + 0x8C) = s7;
        *(s32 *)(sp + 0x90) = vec;
        *(s32 *)(sp + 0x94) = i;
        *(f32 *)(sp + 0xA8) = *(f32 *)(base + 0x18);
        *(f32 *)(sp + 0xAC) = *(f32 *)(*(s32 *)(s5 + 0x24) + 8);
        __builtin_memcpy(sp + 0x50, sp + 0x80, 0x30);

        result = func_00191600(desc);
        *(s32 *)s4 = result;
        s4 += 8;
        result = func_001919C8(result);
        i = i + 1;
    } while (i < 5);
    return result;
}
