#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FL(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern f32 D_00384B64;
extern f32 D_00384B68;
extern f32 D_00384B6C;

s32 rand(void);
void func_00129C28(void *arg0, void *arg1);
void func_00129B58(void *arg0, f32 *arg1, void *arg2);
void func_00129B28(void *arg0, void *arg1, void *arg2);
void func_00129BB8(f32 farg0, void *arg1, void *arg2);
void func_00208DE8(s32 arg0, f32 *arg1, s32 arg2);
void func_00208798(s32 arg0, f32 *arg1);
void func_00208F18(s32 arg0, f32 *arg1, s32 arg2);
void Mtx_RotateY(f32 farg0, f32 *arg1, f32 *arg2);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Vec3_Normalize(void *arg0, void *arg1);
void func_00183A18(void *arg0);
void func_00183B78(void *arg0, s32 arg1, s32 arg2);
void func_00210000(void *arg0, s32 arg1);
void func_0014EAE8(s32 arg0, void *arg1);
void func_001F3738(void *arg0, s32 arg1);

void func_00182EA0(void *arg0, void *arg1) {
    f32 fr[28] __attribute__((aligned(16)));
    f32 temp_f20;
    f32 temp_f0;
    s32 temp_a0;
    void *s5;
    void *s3;
    void *s0;
    void *s4;
    void *s2;
    u8 *v0;
    u8 *v1;

    s5 = *(void **)((u8 *)arg0 + 0x38);
    memset(s5, 0, 0xB30);

    v1 = (u8 *)s5 + 0xA10;
    v0 = (u8 *)arg1;
    do {
        *(s64 *)(v1 + 0x00) = *(s64 *)(v0 + 0x00);
        *(s64 *)(v1 + 0x08) = *(s64 *)(v0 + 0x08);
        *(s64 *)(v1 + 0x10) = *(s64 *)(v0 + 0x10);
        *(s64 *)(v1 + 0x18) = *(s64 *)(v0 + 0x18);
        v0 += 0x20;
        v1 += 0x20;
    } while (v0 != (u8 *)arg1 + 0x40);
    *(s64 *)(v1 + 0x00) = *(s64 *)(v0 + 0x00);
    *(s64 *)(v1 + 0x08) = *(s64 *)(v0 + 0x08);

    s3 = (u8 *)s5 + 0xA70;
    s0 = (u8 *)s5 + 0xA80;
    s4 = (u8 *)s5 + 0xA90;
    func_00129C28((u8 *)s5 + 0xA60, arg1);
    func_00129C28(s3, arg1);
    func_00208DE8(W(arg1, 0x30), fr, 0x11);
    Vec4_Set(s0, fr[0], fr[1], fr[2], 1.0f);
    func_00129C28(s0, fr);
    func_00129C28(s4, (u8 *)arg1 + 0x10);
    func_00129C28((u8 *)s5 + 0xAB0, s3);
    FL(s5, 0xB20) = 6.5f;
    temp_f20 = ((f32)rand() / D_00384B64) * 1.5f;
    func_00208798(W(arg1, 0x30), &fr[4]);
    func_00208F18(W(arg1, 0x30), &fr[8], 0x30);
    Mtx_RotateY(D_00384B68, &fr[8], &fr[8]);
    temp_f20 = temp_f20 + 2.5f;
    temp_f0 = ((f32)(W(arg1, 0x3C) - 2) * -5.0f) - 2.5f;
    fr[7] = 1.0f;
    fr[4] += (fr[16] * 12.0f) + (fr[8] * temp_f0);
    fr[5] += (fr[17] * 12.0f) + (fr[9] * temp_f0);
    fr[6] += (fr[18] * 12.0f) + (fr[10] * temp_f0);

    s2 = (u8 *)s5 + 0xAC0;
    func_00129B58(s2, &fr[4], s3);
    FL(s5, 0xAC4) = FL(s5, 0xAC4) * 0.25f;
    Vec3_Normalize(s2, s2);
    func_00129C28(s4, s2);
    FL(s5, 0xB1C) = temp_f20;
    *(s16 *)((u8 *)s5 + 0xAD4) = -1;
    FL(s5, 0xB18) = D_00384B6C;
    FL(s5, 0xB0C) = 1.0f;
    func_00183A18(s5);
    func_00183B78(s5, 0, 1);
    *(u16 *)((u8 *)s5 + 0xAD6) = (u16)(*(u16 *)((u8 *)s5 + 0xAD6) | 2);
    func_00210000(s3, 0x37);
    func_00129BB8(3.0f, &fr[24], s4);
    func_00129B28((u8 *)s5 + 0xAA0, s3, &fr[24]);
    FL(s5, 0xAAC) = 1.0f;
    temp_a0 = W(s5, 0xA50);
    W(s5, 0xA00) = temp_a0;
    func_0014EAE8(temp_a0, s5);
    func_001F3738(arg0, (W(arg1, 0x30) != 0) ? 0x1000 : 0x800);
}
