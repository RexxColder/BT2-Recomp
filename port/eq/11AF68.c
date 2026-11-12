#include "common.h"

s32 ColBox_Overlaps(u8 *a, u8 *b);
void ColSphere_Set(u8 *out, u8 *center, f32 radius);
s32 ColSphere_SweepSphere(u8 *a, u8 *b, u8 *c, void *d, f32 *out);
s32 ColSphere_TestSphere(u8 *a, u8 *b);
f32 Vec3_Dist(u8 *a, u8 *b);
void func_003126C8(u8 *a, u8 *b);
extern u8 D_002C3630 __attribute__((section(".data")));
extern f32 D_00384048;
void bt2_fightlog_note(const char *fmt, ...);
void func_00312650(void *d, void *a, void *b);
f32 sceVu0InnerProduct(void *a, void *b);

s32 func_0011AF68(u8 *arg0, u8 *arg1) {
    u8 sp[0x40];
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s5;
    s32 s4;
    f32 var_f20;
    f32 sp20;
    f32 X;
    f32 Y;
    f32 Z;
    s32 flag;

    s4 = 0;
    var_f20 = 1.0f;
    s5 = *(u8 **)(arg1 + 0xC);
    if (ColBox_Overlaps(arg1 + 0x84, arg0 + 0xF78) == 0) {
        return 0;
    }
    ColSphere_Set(sp, s5, *(f32 *)(s5 + 0x20));
    s2 = *(u8 **)(arg0 + 0xEF0);
    s3 = arg1 + 0xA0;

    for (;;) {
        s1 = s2 + 0x20;
        s32 sw = ColSphere_SweepSphere(sp, s1, s3, &D_002C3630, (f32 *)(sp + 0x20));
        {   f32 *A = (f32 *)sp, *B = (f32 *)s1, *M = (f32 *)&D_002C3630;
            f32 dx = B[0]-A[0], dy = B[1]-A[1], dz = B[2]-A[2], r = A[4]+B[4];
            f32 vx = M[0]-((f32 *)s3)[0], vy = M[1]-((f32 *)s3)[1], vz = M[2]-((f32 *)s3)[2];
            f32 qc = dx*dx+dy*dy+dz*dz - r*r, qa = vx*vx+vy*vy+vz*vz, qb = vx*dx+vy*dy+vz*dz;
            {   f32 dd[4] __attribute__((aligned(16))); f32 pd;
                func_00312650(dd, s1, sp); pd = sceVu0InnerProduct(dd, dd);
                bt2_fightlog_note("B3B HELP d %g %g %g %g dot %g  rA %g rB %g", dd[0], dd[1], dd[2], dd[3], pd, *(f32 *)(sp + 0x10), *(f32 *)(s1 + 0x10)); }
            f32 t2 = -1.0f; s32 sw2 = ColSphere_SweepSphere(sp, s1, s3, &D_002C3630, &t2);
            bt2_fightlog_note("B3B CALC pila %llx M %g %g %g %g qc %g qa %g qb %g disc %g  sw2 %d t2 %g", (unsigned long long)(__UINTPTR_TYPE__)&t2, M[0], M[1], M[2], M[3], qc, qa, qb, qb*qb-qa*qc, sw2, t2); }
        {   f32 *A = (f32 *)sp, *B = (f32 *)s1, *D = (f32 *)s3;
            bt2_fightlog_note("B3B ESF yo %.0f %.0f %.0f %.0f r %.1f  el %.0f %.0f %.0f %.0f r %.1f  dir %.1f %.1f %.1f  sw %d t %.3f",
                A[0], A[1], A[2], A[3], A[4], B[0], B[1], B[2], B[3], B[4], D[0], D[1], D[2], sw, *(f32 *)(sp + 0x20)); }
        if (sw != 0) {
            sp20 = *(f32 *)(sp + 0x20);
            if (sp20 <= D_00384048 || sp20 >= 1.0f) {
                if (ColSphere_TestSphere(sp, s1) != 0) {
                    func_003126C8(arg1 + 0x20, sp);
                    func_003126C8(arg1 + 0x30, sp);
                    s4 += 1;
                    break;
                }
            } else if (sp20 < var_f20) {
                var_f20 = sp20;
                s4 += 1;
                X = *(f32 *)(sp + 0x0) + sp20 * *(f32 *)(arg1 + 0xA0);
                Y = *(f32 *)(sp + 0x4) + sp20 * *(f32 *)(arg1 + 0xA4);
                Z = *(f32 *)(sp + 0x8) + sp20 * *(f32 *)(arg1 + 0xA8);
                *(f32 *)(arg1 + 0x3C) = 1.0f;
                *(f32 *)(arg1 + 0x20) = X;
                *(f32 *)(arg1 + 0x24) = Y;
                *(f32 *)(arg1 + 0x28) = Z;
                *(f32 *)(arg1 + 0x2C) = 1.0f;
                *(f32 *)(arg1 + 0x30) = X + *(f32 *)(sp + 0x10) * *(f32 *)(arg1 + 0xB0);
                *(f32 *)(arg1 + 0x34) = Y + *(f32 *)(sp + 0x10) * *(f32 *)(arg1 + 0xB4);
                *(f32 *)(arg1 + 0x38) = Z + *(f32 *)(sp + 0x10) * *(f32 *)(arg1 + 0xB8);
            }
        }
        /* flag is read from the record before the 0x1D0 step; the step happens in the branch delay slot */
        flag = *(s32 *)s2;
        s2 += 0x1D0;
        if (flag & 1) {
            break;
        }
    }

    if (s4 != 0) {
        *(f32 *)(arg1 + 0xC0) = Vec3_Dist(s5, arg1 + 0x20);
        return 1;
    }
    return 0;
}
