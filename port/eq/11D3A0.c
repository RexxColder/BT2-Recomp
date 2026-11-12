#include "common.h"

void StgCol_StepSphere(u8 *arg0, u8 *arg1, u8 *arg2);
s32 BtlStage_FindZoneNear(s32 zone, u8 *center);
s32 StgCol_FirstBit(s64 arg0);
s32 func_00273248(s32 arg0);
void func_0011CB00(void);
s32 func_0011CB18(u8 *res, s32 zone, u8 *box, u8 *ctx, void *cb);
void func_0011D298(s32 arg0, s32 arg1);
s32 func_00274680(s32 arg0);
s32 func_0020AA78(s32 arg0);
s32 func_0020AB00(s32 arg0);
void func_00274338(s32 arg0, u8 *arg1);
void func_00312650(f32 *a0, u8 *a1, u8 *a2);
void func_00260A50(u8 *arg0);
void func_00260D48(u8 *arg0);
void func_002605A0(u8 *arg0, s32 arg1);
void func_003126C8(void *arg0, void *arg1);
extern u8 D_002C3630[];

s32 func_0011D3A0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, u8 *arg5, u8 arg6, u8 arg7) {
    u8 sp[0x18];
    u8 *v30 = arg0 + 0xEF0;
    u8 *s1 = arg0 + 0xE50;
    f32 *s6 = (f32 *)(arg0 + 0x9A0);
    u8 *p34 = *(u8 **)(v30 + 0x50);
    s32 fp = arg3;
    s32 s3 = arg2;
    s32 s7;
    s32 s0;
    s32 s2;
    s32 v0;

    if (arg6 != 0) {
        s7 = 0;
    } else {
        s7 = func_00273248(s3);
    }

    for (;;) {
        StgCol_StepSphere(arg1 + 0x10, arg1 + 0x30, arg4);
        if (arg6 != 0) {
            s3 = BtlStage_FindZoneNear(s3, arg1 + 0x10);
            s7 = func_00273248(s3);
        }
        func_0011CB00();
        v0 = func_0011CB18(sp, s7, arg1 + 0x30, arg1, (void *)func_0011D298);
        if (v0 != 0 && sp[3] != 0) {
            s0 = StgCol_FirstBit(*(s64 *)(sp + 0x10));
            if (s0 >= 0) {
                s2 = func_00274680(s0);
                if (func_0020AA78(*(s32 *)arg0) != 0) {
                    v0 = s2 & 0x100;
                } else {
                    v0 = func_0020AB00(*(s32 *)arg0);
                }
                if (v0 != 0) {
                    func_00274338(s0, arg5);
                    *(u32 *)s1 |= 0x40;
                }
                if (*(u32 *)s1 & 0x40) {
                    if (s2 & 0x800) {
                        *(u32 *)s1 |= 0x80;
                    }
                    if (s2 & 0x2000) {
                        *(u32 *)s1 |= 0x100;
                    }
                    if (s2 & 0x1000) {
                        *(u32 *)s1 |= 0x200;
                    }
                }
            }
        }
        fp--;
        if (fp <= 0) {
            break;
        }
    }

    if (arg1[0] == 0) {
        func_003126C8(v30 + 0x60, D_002C3630);
        return 0;
    }

    *(u32 *)s1 |= 0x20;
    *(s64 *)(s1 + 0x80) = *(s64 *)(arg1 + 0x50);
    *(s64 *)(s1 + 0x88) = *(s64 *)(arg1 + 0x58);
    *(s64 *)(s1 + 0x90) = *(s64 *)(arg1 + 0x60);
    *(s64 *)(s1 + 0x98) = *(s64 *)(arg1 + 0x68);
    func_00312650((f32 *)(v30 + 0x60), p34, arg1 + 0x10);

    {
        f32 *pos = (f32 *)(v30 + 0x60);
        f32 f1 = s6[0] - pos[0];
        f32 f2 = s6[1] - *(f32 *)(v30 + 0x64);
        f32 f3 = s6[2] - *(f32 *)(v30 + 0x68);
        s6[0] = f1;
        s6[1] = f2;
        s6[3] = 1.0f;
        s6[2] = f3;
    }

    func_00260A50(arg0);
    func_00260D48(arg0);
    if (arg7 != 0) {
        func_002605A0(arg0, 0);
    } else {
        func_003126C8(p34, arg1 + 0x10);
    }
    return 1;
}
