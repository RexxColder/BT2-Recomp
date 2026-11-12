#include "common.h"

typedef struct { u64 lo, hi; } q128;

extern u8 D_0036F160[120];
extern f32 D_00385540;
extern f32 D_00385544;

extern f32 BtlCharApi_GetHeight(s32 a);
extern s32 Vec4_Set(f32 *v, f32 x, f32 y, f32 z, f32 w);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
void func_00129C28(q128 *arg0, q128 *arg1);
void Vec4_Sub(u8 *arg0, u8 *arg1, u8 *arg2);
f32 func_001DA640(u8 *arg0);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
s32 rand(void);
void func_001D4678(s32 arg0, u8 *a1, u8 *a2, u8 *a3, u8 *a4, s32 a5, s32 a6, s32 a7,
                   f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                   f32 st0, f32 st1, f32 st2, f32 st3);

#define P(x) ((s32)(u32)(x))

/* Scatters sparks along 10 segments of a character (table of joint pairs at D_0036F160, 12 bytes each:
   joint a, joint b, flag byte); one spark per `minLen` of segment length. Note the original decrements the
   entry counter once per spark, not once per entry. */
void func_001D8AE8(s32 obj, u64 *dirIn, f32 scale, f32 farg1) {
    f32 dir[4];          /* spark direction (copied from the caller) */
    f32 start[4];        /* segment start (also reused as spark position) */
    f32 startCopy[4];
    f32 step[4];
    f32 diff[4];
    f32 colA[4];
    f32 colB[4];
    f32 minLen = BtlCharApi_GetHeight(obj) * 0.25f;
    s32 entry = 0;       /* byte offset in the table */
    s32 left = 9;
    s32 count, i, b, r;
    u8 *e;
    f32 len, r1, r2, r3, r4, r5, sz, spin, dirSel;

    if (minLen < 6.0f) {
        minLen = 6.0f;
    }
    *(u64 *)&dir[0] = dirIn[0];
    *(u64 *)&dir[2] = dirIn[1];
    do {
        e = D_0036F160 + entry;
        func_00208DE8(obj, P(start), *(s32 *)e);
        func_00129C28((q128 *)startCopy, (q128 *)start);
        b = *(s32 *)(e + 4);
        i = 0;
        if (b < 0) {
            Vec4_Set(step, 0.0f, 0.0f, 0.0f, 1.0f);
            count = 1;
        } else {
            func_00208DE8(obj, P(diff), b);
            Vec4_Sub((u8 *)diff, (u8 *)diff, (u8 *)start);
            len = func_001DA640((u8 *)diff);
            if (minLen < len) {
                count = (s32)(len / minLen + 1.0f);
                Vec3_Scale((u8 *)step, (u8 *)diff, 1.0f / (f32)count);
            } else {
                Vec4_Set(step, 0.0f, 0.0f, 0.0f, 1.0f);
                count = 1;
                if (e[8] != 0) {
                    count = 0;
                }
            }
        }
        if (count <= 0) {
            left--;
        } else {
            do {
                r1 = (f32)rand();
                r2 = (f32)rand();
                r3 = (f32)rand();
                r4 = (f32)rand();
                start[0] = startCopy[0] + (f32)i * step[0];
                start[1] = (startCopy[1] + (f32)i * step[1]) + scale * 6.0f;
                start[2] = startCopy[2] + (f32)i * step[2];
                i++;
                sz = (r4 / D_00385540) * 0.5f + 1.0f;
                Vec4_Set(colA, 128.0f, 128.0f, 128.0f, 0.0f);
                r = rand();
                Vec4_Set(colB, 128.0f, 128.0f, 128.0f, (f32)(128 - (r % 32)));
                dir[3] = 1.0f;
                start[3] = 1.0f;
                r5 = (f32)rand();
                spin = (r5 / D_00385540) * 360.0f;
                dirSel = (rand() & 1) ? 2.0f : -2.0f;
                func_001D4678(obj, (u8 *)start, (u8 *)dir, (u8 *)colA, (u8 *)colB, 0, 0xB, 0,
                              ((r1 / D_00385540) * 1.5f + 2.0f) * scale, -3.0f,
                              ((r2 / D_00385540) * 1.5f + minLen) * scale,
                              (r3 / D_00385540 + 1.5f) * scale,
                              (((r2 / D_00385540) * 1.5f + minLen) * scale) * 4.0f, spin, dirSel, D_00385544,
                              0.0f, sz, 0.0f, farg1);
                left--;
            } while (i < count);
        }
        entry += 12;
    } while (left >= 0);
}
