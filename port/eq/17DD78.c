#include "common.h"

extern f32 D_00384AA4;
extern f32 D_00384AA8;
extern f32 D_00384AAC;
extern f32 D_00384AB0;
extern f32 D_00384AB4;
extern f32 D_00384AB8;
extern f32 D_00384ABC;
extern f32 D_00384AC0;

void *memset(void *a0, s32 a1, u32 a2);
s32 rand(void);
void sceVu0Normalize(void *a0, void *a1);
void func_00312650(void *a0, void *a1, void *a2);
void func_00312680(f32 f, void *a0, void *a1);

#define NODE_F(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define NODE_W(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 EftBolt_Step(void *arg0, f32 farg) {
    u8 sp[0x10];
    u8 *s2 = (u8 *)arg0;
    u8 *s1;
    s32 s3 = 0;
    s32 s4 = 0;
    s32 a1v;
    s32 orig;
    s32 flags;
    s32 r1;
    s32 r2;
    s32 r3;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    f32 f7;
    f32 x;
    f32 y;

    memset(sp, 0, 0x10);
    s1 = (u8 *)NODE_W(s2, 0);
    if (s1 == NULL) {
        return s4;
    }

    do {
        a1v = NODE_W(s1, 0x30);
        if (NODE_W(s2, 0xC) & 2) {
            orig = NODE_W(s1, 0);
            flags = orig | 2;
            NODE_W(s1, 0) = flags;
            if (!(flags & 0x10) && ((NODE_W(s2, 8) - NODE_W(s2, 4)) >= s3)) {
                NODE_W(s1, 0) = orig | 0x12;
            }
        } else if (NODE_W(s2, 4) >= s3) {
            NODE_W(s1, 0) = NODE_W(s1, 0) | 2;
        }

        flags = NODE_W(s1, 0);
        if (!(flags & 8)) {
            if (flags & 2) {
                f0 = NODE_F(s1, 0xC);
                if (!(flags & 4)) {
                    NODE_F(s1, 0x2C) = f0 * D_00384AA4;
                    if (flags & 0x20) {
                        if (NODE_W(s2, 0x10) < 4) {
                            x = NODE_F(s1, 4) * 5.5f;
                            y = NODE_F(s1, 8) * 5.5f;
                        } else {
                            x = NODE_F(s1, 4) * 2.75f;
                            y = NODE_F(s1, 8) * 2.75f;
                        }
                        NODE_F(s1, 4) = x;
                        NODE_F(s1, 8) = y;
                    }
                    NODE_W(s1, 0) = flags | 4;
                } else {
                    NODE_F(s1, 0x2C) = f0;
                    if (flags & 0x20) {
                        if (NODE_W(s2, 0x10) < 4) {
                            x = NODE_F(s1, 4) * D_00384AA8;
                            y = NODE_F(s1, 8) * D_00384AA8;
                        } else {
                            x = NODE_F(s1, 4) * D_00384AAC;
                            y = NODE_F(s1, 8) * D_00384AAC;
                        }
                        NODE_F(s1, 4) = x;
                        NODE_F(s1, 8) = y;
                    }
                    NODE_W(s1, 0) = flags | 8;
                }
            }
        } else if (flags & 0x10) {
            NODE_F(s1, 4) = NODE_F(s1, 4) * D_00384AB0;
            NODE_F(s1, 8) = NODE_F(s1, 8) * D_00384AB0;
            if (a1v != 0) {
                func_00312650(sp, (u8 *)a1v + 0x10, s1 + 0x10);
                f0 = NODE_F(sp, 0);
            } else {
                r1 = rand();
                f0 = (f32)r1;
                f4 = D_00384AB8;
                f2 = NODE_F(s2, 0x70);
                f3 = NODE_F(s2, 0x74);
                f1 = NODE_F(s2, 0x78);
                f0 = f0 / D_00384AB4;
                f0 = f0 * f4;
                f1 = f1 * f0;
                f2 = f2 * f0;
                f3 = f3 * f0;
                NODE_F(sp, 8) = f1;
                NODE_F(sp, 0) = f2;
                NODE_F(sp, 4) = f3;
                r2 = rand();
                r3 = rand();
                f1 = (f32)r3;
                f0 = (f32)r2;
                f6 = NODE_F(s2, 0x80);
                f7 = NODE_F(s2, 0x84);
                f3 = NODE_F(s2, 0x88);
                f4 = NODE_F(sp, 0);
                f5 = NODE_F(sp, 4);
                f2 = NODE_F(sp, 8);
                f1 = f1 / D_00384AB4;
                f0 = f0 / D_00384AB4;
                f1 = f1 * D_00384AA4;
                f0 = f0 * D_00384AA4;
                f0 = f0 - f1;
                f0 = f0 - D_00384AA8;
                f3 = f3 * f0;
                f6 = f6 * f0;
                f7 = f7 * f0;
                f2 = f2 + f3;
                f4 = f4 + f6;
                f5 = f5 + f7;
                NODE_F(sp, 8) = f2;
                NODE_F(sp, 0) = f4;
                NODE_F(sp, 4) = f5;
                sceVu0Normalize(sp, sp);
                func_00312680(farg * D_00384ABC, sp, sp);
                f0 = NODE_F(sp, 0);
            }

            NODE_F(s1, 0x10) = NODE_F(s1, 0x10) + f0;
            f4 = NODE_F(s1, 0xC);
            f2 = f4 * 0.25f;
            f5 = NODE_F(s1, 0x14);
            f3 = NODE_F(s1, 0x2C) - f2;
            f5 = f5 + NODE_F(sp, 4);
            NODE_F(s1, 0x14) = f5;
            NODE_F(s1, 0x2C) = f3;
            f1 = NODE_F(s1, 0x18) + NODE_F(sp, 8);
            NODE_F(s1, 0x18) = f1;
            f4 = f4 * D_00384AC0;
            if (f3 <= f4) {
                NODE_F(s1, 0x2C) = f4;
                if (s3 >= (NODE_W(s2, 8) - 1)) {
                    s4 = 1;
                }
            }
        }

        s1 = (u8 *)a1v;
        s3 += 1;
    } while (s1 != NULL);

    return s4;
}
