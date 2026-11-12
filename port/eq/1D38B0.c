#include "common.h"

extern u8 *func_001D3028(void);
extern void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern f32 Mathf_Cos(f32 farg0);
extern f32 func_0012A3F8(f32 farg0);
extern void func_00129C28(void *arg0, void *arg1);
extern s32 rand(void);
extern u8 *D_00387E9C;
extern u8 D_00342F40[];
extern u8 D_00342ED0[];
extern f32 D_003854A0;

/* Spawns one burst particle at a position with a random direction on the unit sphere:
   speed/colour/life fields from the float params, colour keys either from the palette tables
   (index >= 0) or from the default grey, then counts it. Returns the new live count. */
s32 func_001D38B0(f32 *pos, s32 flag, s32 alpha, s32 palIdx,
                  f32 scaleDir, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7,
                  f32 speed, f32 life, f32 extra) {
    f32 sp[16];
    f32 *p0 = &sp[0];
    f32 *grey = &sp[4];
    f32 *greyB = &sp[8];
    u8 *rec;
    f32 sinA;
    f32 a;
    f32 b;
    f32 c;
    f32 t;

    sp[0] = pos[0];
    sp[1] = pos[1];
    sp[2] = pos[2];
    sp[3] = pos[3];
    Vec4_Set(grey, 128.0f, 128.0f, 128.0f, (f32)alpha);
    Vec4_Set(greyB, 128.0f, 128.0f, 128.0f, 0.0f);
    rec = func_001D3028();
    if (rec == 0) {
        return 0;
    }
    *(f32 *)(rec + 0x68) = scaleDir;
    t = (f32)(rand() % 360) / 180.0f * D_003854A0;
    sinA = func_0012A3F8(t);
    *(f32 *)(rec + 0x18) = Mathf_Cos(t);
    t = (f32)(rand() % 360) / 180.0f * D_003854A0;
    *(f32 *)(rec + 0x10) = Mathf_Cos(t) * sinA;
    *(f32 *)(rec + 0x14) = func_0012A3F8(t) * sinA;

    a = *(f32 *)(rec + 0x10);
    b = *(f32 *)(rec + 0x14);
    c = *(f32 *)(rec + 0x18);
    *(f32 *)(rec + 0x20) = p0[0] + a * speed;
    *(f32 *)(rec + 0x24) = p0[1] + b * speed;
    *(f32 *)(rec + 0x10) = a * *(f32 *)(rec + 0x68);
    *(f32 *)(rec + 0x14) = b * *(f32 *)(rec + 0x68);
    *(f32 *)(rec + 0x18) = c * *(f32 *)(rec + 0x68);
    *(f32 *)(rec + 0x64) = f7;
    *(f32 *)(rec + 0x6C) = f1;
    *(f32 *)(rec + 0x28) = p0[2] + c * speed;
    *(f32 *)(rec + 0x70) = f2;
    *(f32 *)(rec + 0x74) = f3;
    *(f32 *)(rec + 0x78) = f4;
    *(f32 *)(rec + 0x7C) = f5;
    *(f32 *)(rec + 0x60) = f6;
    *(f32 *)(rec + 0x84) = 1.0f / (life * 30.0f);
    *(f32 *)(rec + 0x80) = 1.0f;
    *(s32 *)(rec + 0x94) = palIdx;
    if (palIdx >= 0) {
        rec[0x91] = 1;
        rec[0x90] = rec[0x94] + 1;
        func_00129C28(rec + 0x30, D_00342F40 + palIdx * 16);
        func_00129C28(rec + 0x40, D_00342F40 + *(s32 *)(rec + 0x94) * 16);
        func_00129C28(rec + 0x50, D_00342ED0 + *(s32 *)(rec + 0x94) * 16);
    } else {
        rec[0x91] = 0;
        rec[0x90] = 11;
        func_00129C28(rec + 0x30, grey);
        func_00129C28(rec + 0x40, grey);
        func_00129C28(rec + 0x50, greyB);
    }
    rec[0x93] = flag;
    *(f32 *)(rec + 0x8C) = extra;
    rec[0x99] = 1;
    *(s32 *)(rec + 0x88) = 0;
    rec[0x92] = 1;
    rec[0x98] = 0;
    *(s32 *)(D_00387E9C + 0x1424) = *(s32 *)(D_00387E9C + 0x1424) + 1;
    return *(s32 *)(D_00387E9C + 0x1424);
}
