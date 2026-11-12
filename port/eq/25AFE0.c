#include "common.h"

#define FLD(o, off) (*(f32 *)((u8 *)(o) + (off)))
#define FSET(o, off, v) (*(f32 *)((u8 *)(o) + (off)) = (v))
#define WSET(o, off, v) (*(s32 *)((u8 *)(o) + (off)) = (v))

void sceVu0UnitMatrix(void *m);
void sceVu0MulMatrix(void *m0, void *m1, void *m2);

void func_0025AFE0(void *obj) {
    f32 sp[16];
    void *s1 = (u8 *)obj + 0x40;
    void *s2 = (u8 *)obj + 0x80;
    void *s3 = (u8 *)obj + 0xC0;
    f32 t3;
    f32 t21;
    f32 t4;
    f32 t0;
    f32 t5;
    f32 t22;
    f32 t3s;
    f32 d4;
    f32 f20;
    f32 f23;
    f32 f21b;
    f32 f22b;
    f32 f24;
    f32 f25;
    f32 a;
    f32 b;
    f32 d;
    f32 t1b;
    f32 t3b;

    t3 = FLD(obj, 0x23C);
    t21 = FLD(obj, 0x240);
    t4 = FLD(obj, 0x244);
    t0 = FLD(obj, 0x238);
    t5 = FLD(obj, 0x214);
    t22 = FLD(obj, 0x210);
    t3s = FLD(obj, 0x224);
    d4 = t4 - t21;
    f23 = (t4 * t21 * (t3 - t0)) / d4;
    f20 = ((-t3 * t21) + (t0 * t4)) / d4;
    f21b = (t21 * t5) / t3s;
    f22b = (t21 * t22) / t3s;
    f24 = (FLD(obj, 0x234) - 2048.0f) / (t5 * FLD(obj, 0x22C));
    f25 = (FLD(obj, 0x230) - 2048.0f) / (t22 * FLD(obj, 0x228));

    sceVu0UnitMatrix(s1);
    FSET(obj, 0x40, t3s * FLD(obj, 0x248));
    FSET(obj, 0x78, 1.0f);
    FSET(obj, 0x6C, 1.0f);
    WSET(obj, 0x68, 0);
    WSET(obj, 0x7C, 0);
    FSET(obj, 0x54, t3s * FLD(obj, 0x248));

    sceVu0UnitMatrix(sp);
    sp[0] = FLD(obj, 0x228);
    sp[5] = FLD(obj, 0x22C);
    sp[10] = f23;
    sp[12] = FLD(obj, 0x230);
    sp[13] = FLD(obj, 0x234);
    sp[14] = f20;
    sceVu0MulMatrix(s1, sp, s1);

    sceVu0UnitMatrix(s2);
    FSET(obj, 0x80, ((2.0f * FLD(obj, 0x240)) / (2.0f * f22b)) * FLD(obj, 0x248));
    FSET(obj, 0xAC, 1.0f);
    a = FLD(obj, 0x240);
    b = FLD(obj, 0x244);
    WSET(obj, 0xBC, 0);
    d = b - a;
    FSET(obj, 0x94, ((2.0f * a) / (2.0f * f21b)) * FLD(obj, 0x248));
    FSET(obj, 0xA8, (b + a) / d);
    FSET(obj, 0xB8, (b * a * -2.0f) / d);

    sceVu0UnitMatrix(sp);
    sp[12] = f25;
    sp[13] = f24;
    sceVu0MulMatrix(s2, sp, s2);

    sceVu0UnitMatrix(s3);
    FSET(obj, 0xC0, ((t3s * FLD(obj, 0x228)) * f22b) / FLD(obj, 0x240));
    FSET(obj, 0xFC, 1.0f);
    t1b = FLD(obj, 0x238);
    t3b = FLD(obj, 0x23C);
    FSET(obj, 0xF4, 2048.0f);
    FSET(obj, 0xF0, 2048.0f);
    FSET(obj, 0xF8, (t3b + t1b) * 0.5f);
    FSET(obj, 0xE8, (t1b - t3b) * 0.5f);
    FSET(obj, 0xD4, ((t3s * FLD(obj, 0x22C)) * f21b) / FLD(obj, 0x240));
}
