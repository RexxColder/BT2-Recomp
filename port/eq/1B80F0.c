#include "common.h"

#define FL(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern f32 D_00385058;
extern f32 D_0038505C;
extern f32 D_00385060;

void *func_001B8028(void *arg0);
void *memset(void *arg0, s32 arg1, s32 arg2);
s32 rand(void);
void func_00312638(void *arg0, void *arg1, f32 *arg2);
void func_00312680(f32 farg0, void *arg1, void *arg2);
void sceVu0Normalize(void *arg0, void *arg1);
void sceVu0UnitMatrix(void *arg0);
void sceVu0RotMatrix(void *arg0, void *arg1, void *arg2);
void sceVu0ApplyMatrix(void *arg0, void *arg1, void *arg2);

void *func_001B80F0(void *arg0, f32 farg0) {
    f32 sp[32];
    s32 rA;
    s32 rB;
    s32 rC;
    s32 rD;
    s32 rE;
    s32 rF;
    s32 rG;
    s32 rR;
    f32 f20;
    f32 f22;
    f32 f21;
    f32 t;
    f32 fac;
    f32 X;
    f32 Y;
    f32 Z;
    void *temp_s2;
    void *temp_s0;
    void *var_v0;

    temp_s2 = func_001B8028(arg0);
    memset(sp, 0, 0x10);
    sp[3] = 1.0f;
    memset(&sp[4], 0, 0x10);
    sp[7] = 1.0f;

    rR = rand();
    f22 = D_00385058;
    f21 = D_0038505C;
    f20 = D_00385060;
    X = (((f32)rR) / f22) * f21 - f20;
    rR = rand();
    Y = (((f32)rR) / f22) * f21 - f20;
    rR = rand();
    Z = (((f32)rR) / f22) * f21 - f20;
    sp[8] = X;
    sp[9] = Y;
    sp[10] = Z;
    sp[11] = 1.0f;

    var_v0 = NULL;
    if (temp_s2 != NULL) {
        temp_s0 = (u8 *)temp_s2 + 0x10;
        rA = rand();
        FL(temp_s2, 0x44) = FL(arg0, 0x30) + (FL(arg0, 0x34) * ((f32)rA / f22));
        FL(temp_s2, 0x4C) = farg0;
        FL(temp_s2, 0x50) = FL(arg0, 0x40);
        W(temp_s2, 0x5C) = 1;
        FL(temp_s2, 0x40) = FL(arg0, 0x38);
        W(temp_s2, 0x3C) = 0x80;
        W(temp_s2, 0x30) = 0x80;
        W(temp_s2, 0x34) = 0x80;
        W(temp_s2, 0x38) = 0x80;
        W(temp_s2, 0x58) = W(arg0, 0x64);

        rB = rand();
        t = (f32)rB / f22;
        fac = t + t - 1.0f;
        sp[0] = FL(arg0, 0x44) * fac;
        rC = rand();
        t = (f32)rC / f22;
        fac = t + t - 1.0f;
        sp[1] = FL(arg0, 0x44) * fac;
        rD = rand();
        t = (f32)rD / f22;
        fac = t + t - 1.0f;
        sp[2] = FL(arg0, 0x44) * fac;
        func_00312638(temp_s0, (u8 *)arg0 + 0x10, sp);
        sceVu0Normalize(temp_s0, temp_s0);
        func_00312680(FL(temp_s2, 0x44), (u8 *)temp_s2 + 0x20, temp_s0);

        f20 = FL(arg0, 0x4C) - FL(arg0, 0x50);
        rE = rand();
        sp[4] = FL(arg0, 0x50) + (f20 * ((f32)rE / f22));
        rF = rand();
        sp[5] = FL(arg0, 0x50) + (f20 * ((f32)rF / f22));
        rG = rand();
        sp[6] = FL(arg0, 0x50) + (f20 * ((f32)rG / f22));
        sp[7] = 1.0f;

        sceVu0UnitMatrix(&sp[16]);
        sceVu0RotMatrix(&sp[16], &sp[16], &sp[8]);
        sceVu0ApplyMatrix(&sp[4], &sp[16], &sp[4]);
        func_00312638(temp_s2, arg0, &sp[4]);
        var_v0 = temp_s2;
        W(arg0, 0x74) = W(arg0, 0x74) + 1;
    }
    return var_v0;
}
