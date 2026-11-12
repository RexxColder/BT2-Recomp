#include "common.h"

#define FP(p, o) (*(u8 **)((u8 *)(p) + (o)))
#define FW(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FU(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define FF(p, o) (*(f32 *)((u8 *)(p) + (o)))

extern u8 *D_00387758;
extern u8 *D_003876A0;
extern f32 D_00384558;
extern f32 D_0038455C;
extern f32 D_00384560;
extern f32 D_00384564;
extern f32 D_00384568;
extern u8 D_003B0580[] __attribute__((section(".data")));

void *func_0028BAA8(s32 arg0);
void EftTexSet_Load32(u8 *arg0, u8 *arg1);
void func_00312638(u8 *arg0, u8 *arg1, void *arg2);
void func_00312680(f32 farg0, void *arg1, void *arg2);
void func_003126C8(u8 *arg0, u8 *arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
s32 rand(void);
void sceVu0Normalize(void *arg0, void *arg1);

void func_00146D78(void) {
    f32 vec[4];
    u8 *base;
    u8 *obj;
    u8 *p;
    u8 *s0;
    u8 *s1;
    u8 *s3;
    u8 *s6;
    u8 *q;
    s32 s2;
    s32 s4;
    s32 v;
    s32 cnt;
    s32 rA;
    s32 rB;
    s32 rC;
    s32 rD;
    s32 rE;
    s32 s2sq;
    f32 f20;
    f32 f21;
    f32 f12;

    base = func_0028BAA8(0x2C220);
    D_00387758 = base;
    memset(base, 0, 0x2C220);

    obj = D_003876A0;
    if (*(s64 *)(obj + 0x4D8) & ((s64)0x8000 << 47)) {
        p = FP(obj, 4) + 0x40;
    } else {
        p = FP(obj, 4);
    }
    FP(base, 0x2C210) = p + ((FU(p, 0x3C) >> 2) << 2);
    FP(base, 0x2C20C) = p + ((FU(p, 0x20) >> 2) << 2);
    EftTexSet_Load32(base + 0x2C000, FP(base, 0x2C20C));
    memset(D_003B0580, 0, 0x110);

    s0 = FP(base, 0x2C210);
    if (FW(s0, 0x18) == 0) {
        FU(s0, 0xC) = FU(s0, 0xC) + (u32)s0;
        FW(s0, 0x18) = 1;
        FU(s0, 0x14) = FU(s0, 0x14) + (u32)s0;
    }
    s3 = FP(s0, 0xC);
    s6 = s3;
    f20 = D_00384558;
    f21 = D_0038455C;

    /* loop 1: 512 particles, 0x40 bytes each, from the start of the buffer */
    s1 = base;
    s2 = 0x1FF;
    do {
        s2 -= 1;
        rA = rand();
        FF(s1, 0) = (f32)((rA & 0x1FFF) - 0xFFF) * f20;
        rB = rand();
        FF(s1, 4) = (f32)((rB & 0x1FFF) - 0xFFF) * f20;
        rC = rand();
        FF(s1, 0xC) = 1.0f;
        FW(s1, 0x10) = 0;
        FF(s1, 0x14) = f21;
        FW(s1, 0x18) = 0;
        FW(s1, 0x1C) = 0;
        FF(s1, 8) = (f32)((rC & 0x1FFF) - 0xFFF) * f20;
        s1 += 0x40;
    } while (s2 >= 0);

    s4 = FW(s0, 8);
    s1 = base + 0x8000;
    if (s4 != 0) {
        do {
            if (FW(s3, 0x30) == 0) {
                cnt = FW(D_003B0580, 0x100);
                if (cnt < 0x10) {
                    q = (u8 *)D_003B0580 + (cnt << 4);
                    func_003126C8(q, s3);
                    FF(q, 0xC) = FF(s3, 0x10);
                    FW(D_003B0580, 0x100) = FW(D_003B0580, 0x100) + 1;
                }
            }
            if (FW(s3, 0x30) == 1) {
                f21 = D_00384560;
                s2 = 0;
                do {
                    rA = rand();
                    vec[0] = (f32)((rA & 0x1FFF) - 0xFFF) * f21;
                    rB = rand();
                    vec[1] = (f32)((rB & 0x1FFF) - 0xFFF) * D_00384564;
                    rC = rand();
                    vec[2] = (f32)((rC & 0x1FFF) - 0xFFF) * f21;
                    vec[3] = 0.0f;
                    sceVu0Normalize(vec, vec);

                    rD = rand();
                    s2sq = s2 * s2;
                    s2 += 1;
                    f12 = (f32)((rD & 0x1F) - 0xF) * D_00384568
                        + (1.0f - (f32)s2sq * 0.0009765625f) * 30.0f + 4.0f;
                    func_00312680(f12, vec, vec);
                    func_003126C8(s1, s3);
                    func_00312638(s1, s1, vec);
                    FF(s1, 0xC) = 1.0f;
                    FW(s1, 0x10) = 0;
                    FW(s1, 0x14) = 0;
                    FW(s1, 0x18) = 0;
                    FW(s1, 0x1C) = 0;
                    FP(s1, 0x30) = s6 + ((u32)FW(s3, 0x34) << 6);
                    rE = rand();
                    FW(s1, 0x28) = (rE & 1) ? 1 : 0;
                    s1 += 0x40;
                } while (s2 < 0x20);
            }
            s4 -= 1;
            s3 += 0x40;
        } while (s4 != 0);
    }

    v = ((s32)((u32)s1 - (u32)base) - 0x8000) >> 6;
    if (v < 0x900) {
        do {
            FW(s1, 0x28) = -1;
            s1 += 0x40;
        } while ((((s32)((u32)s1 - (u32)base) - 0x8000) >> 6) < 0x900);
    }
}
