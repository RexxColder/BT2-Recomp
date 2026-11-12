#include "common.h"

extern u8 *D_00387E9C;
extern f32 D_0038544C;
extern f32 D_00385450;
extern f32 D_00385454;
extern f32 D_00385458;
extern f32 D_0038545C;
extern f32 D_00385460;
extern f32 D_00385464;
extern f32 D_00385468;
extern f32 D_0038546C;
extern f32 D_00385470;
extern f32 D_00385474;
extern f32 D_00385478;
extern f32 D_0038547C;
extern f32 D_00385480;
extern f32 D_00385484;
extern f32 D_00385488;
extern f32 D_0038548C;
extern f32 D_00385490;

s32 rand(void);
f32 BtlCharApi_GetHeight(s32 arg0);
f32 EftMath_WrapAngle(f32 farg0);
f32 func_0012A3F8(f32 farg0);
f32 Mathf_Cos(f32 farg0);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Vec3_Normalize(void *arg0, void *arg1);
void func_00129BB8(f32 farg0, void *arg0, void *arg1);
void func_00129B28(void *arg0, s32 arg1, void *arg2);
void func_00129C28(void *arg0, s32 arg1);
void func_001D7778(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 stack0, s32 pad0, f32 stack1, s32 pad1);
void func_001D4678(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   s32 arg0, void *arg1, void *arg2, void *arg3, void *arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 stack0, s32 pad0, f32 stack1, s32 pad1, f32 stack2, s32 pad2, f32 stack3, s32 pad3);

s32 func_001D2288(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2) {
    u8 sp[0x120];
    f32 f30;
    f32 f31;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f12;
    f32 f14;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 f25;
    f32 f26;
    f32 f27;
    f32 f28;
    f32 f29;
    u8 *s0;
    u8 *s3;
    u8 *s5;
    s32 s2;
    s32 result;
    s32 r;

    result = 0;
    f31 = farg1;
    f30 = farg2;
    *(f32 *)(sp + 0x70) = farg0;
    if (*(u8 *)(D_00387E9C + 0x1491) != 0) {
        s2 = 0;
        s0 = sp + 0x30;
        s3 = sp + 0x40;
        f24 = D_0038544C;
        f28 = 2.0f;
        f26 = 0.0f;
        f25 = 1.0f;
        f27 = D_00385458;
        *(f32 *)(sp + 0x78) = D_00385454;
        *(f32 *)(sp + 0x74) = (((f32)rand()) / f24) * D_00385450;

        do {
            f12 = (f32)s2;
            s2 += 1;
            f0 = *(f32 *)(sp + 0x78);
            f1 = *(f32 *)(sp + 0x74);
            f12 = f0 * f12;
            f12 = f1 + f12;
            f21 = EftMath_WrapAngle(f12);
            f20 = func_0012A3F8(f21);
            f14 = Mathf_Cos(f21);
            Vec4_Set(s0, f20, f26, f14, f25);
            Vec3_Normalize(s0, s0);
            func_00129BB8(f28, sp + 0x40, s0);
            func_00129B28(sp + 0x20, arg0, sp + 0x40);

            f22 = (f32)rand();
            f21 = (f32)rand();
            f22 = f22 / f24;
            f21 = f21 / f24;
            f22 = f22 * 3.0f;
            f22 = f22 + f28;
            f21 = f21 * 6.0f;
            f22 = f22 * f31;
            f21 = f21 + 18.0f;
            f23 = (f32)rand();
            f21 = f21 * f30;
            f23 = f23 / f24;
            f23 = f23 * 32.0f;
            f23 = f23 + 148.0f;
            f20 = (f32)rand();
            f20 = f20 / f24;
            f20 = f20 * D_0038545C;
            f20 = f20 + D_00385460;
            f0 = BtlCharApi_GetHeight(arg2);
            f0 = f0 * f27;
            f22 = f22 * f0;
            f0 = BtlCharApi_GetHeight(arg2);
            f0 = f0 * f27;
            f21 = f21 * f0;
            f12 = (f32)rand();
            f12 = f12 / f24;
            f0 = D_00385464;
            f1 = D_00385468;
            f2 = *(f32 *)(sp + 0x70);
            f12 = f12 * f0;
            f12 = f12 + f1;
            func_001D7778(f12, f22, f21, -3.5f, f23, f20, 1.0f, 1.0f,
                          sp + 0x20, arg1, s0, 0x80, 0x80, 0x80, 8, 0,
                          f26, 0, f2, 0);
        } while (s2 < 4);

        f31 = 0.0f;
        r = rand();
        f0 = D_0038546C;
        f1 = (f32)r;
        f2 = D_00385470;
        f3 = D_00385474;
        f30 = 128.0f;
        f28 = D_0038546C;
        *(f32 *)(sp + 0x78) = f3;
        s2 = 0;
        f1 = f1 / f0;
        f27 = D_00385478;
        s5 = sp + 0x50;
        s3 = sp + 0x60;
        s0 = sp + 0x30;
        f1 = f1 * f2;
        *(f32 *)(sp + 0x74) = f1;

        do {
            Vec4_Set(s5, f30, f30, 168.0f, f31);
            r = rand();
            {
                s32 t = r + 0xF;
                s32 v1 = (r < 0) ? t : r;
                s32 v0;
                v1 = v1 >> 4;
                v1 = v1 << 4;
                v0 = r - v1;
                Vec4_Set(s3, f30, f30, f30, (f32)(0xA8 - v0));
            }
            func_00129C28(sp + 0x20, arg0);
            *(f32 *)(sp + 0x24) = *(f32 *)(sp + 0x24) - 6.0f;

            f26 = (((f32)rand()) / f28) * 3.0f + 4.5f;
            f25 = (((f32)rand()) / f28) * 3.0f + 4.0f;
            f24 = (((f32)rand()) / f28) * 3.0f + 4.0f;
            f23 = (((f32)rand()) / f28) * 7.0f + 23.0f;
            f22 = (((f32)rand()) / f28) * D_0038547C + D_00385480;
            f29 = (((f32)rand()) / f28) * D_00385484 + D_00385488;

            f0 = BtlCharApi_GetHeight(arg2);
            f0 = f0 * f27;
            f26 = f26 * f0;
            f0 = BtlCharApi_GetHeight(arg2);
            f0 = f0 * f27;
            f25 = f25 * f0;
            f0 = BtlCharApi_GetHeight(arg2);
            f0 = f0 * f27;
            f24 = f24 * f0;
            f0 = BtlCharApi_GetHeight(arg2);
            f0 = f0 * f27;
            f23 = f23 * f0;
            f0 = BtlCharApi_GetHeight(arg2);
            f0 = f0 * f27;
            f22 = f22 * f0;

            f12 = (f32)s2;
            f0 = *(f32 *)(sp + 0x78);
            f1 = *(f32 *)(sp + 0x74);
            f12 = f0 * f12;
            f12 = f1 + f12;
            f21 = EftMath_WrapAngle(f12);
            f20 = func_0012A3F8(f21);
            f14 = Mathf_Cos(f21);
            Vec4_Set(s0, f20, f31, f14, 1.0f);
            Vec3_Normalize(s0, s0);

            r = rand();
            if ((r & 1) != 0) {
                f0 = D_0038548C;
            } else {
                f0 = D_00385490;
            }
            f2 = *(f32 *)(sp + 0x70);
            s2 += 1;
            func_001D4678(f26, -4.5f, f25, f24, f23, f31, f0, -f22,
                          0, sp + 0x20, s0, s5, s3, 0, 0xB, 0,
                          f31, 0, f29, 0, f27, 0, f2, 0);
        } while (s2 < 8);
        result = 1;
    }
    return result;
}
