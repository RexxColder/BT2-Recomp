#include "common.h"

#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define S32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define PTR(p, off) (*(u8 **)((u8 *)(p) + (off)))

extern u8 *gEftMod1CBMgr;
extern f32 D_003851B0;

void Vec3_Add(u8 *a0, u8 *a1, u8 *a2);
void Vec3_Normalize(u8 *a0, u8 *a1);
void func_00129B28(u8 *a0, u8 *a1, u8 *a2);
void func_00129D68(u8 *a0, u8 *a1, f32 f12, f32 f13);
void func_0012A360(f32 f12, u8 *a0, u8 *a1, u8 *a2, s32 a3);
s32 rand(void);

void func_001C9E48(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 sp[2];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *nxt;
    u8 *base;
    s32 idx;
    s32 t2;
    s32 e;
    s32 v1;
    f32 f0;
    f32 f1;
    f32 f20;
    f32 r;

    sp[0] = S32(gEftMod1CBMgr, 0x270);
    sp[1] = sp[0] + 0x40;

    s2 = PTR(arg1, 0);
    if (s2 == NULL) {
        return;
    }
    do {
        if (!(F32(s2, 0xC) < F32(s2, 0x10))) {
            /* remove s2 from the list */
            nxt = PTR(s2, 0x134);
            S32(s2, 0) = 0;
            if (nxt != NULL) {
                PTR(nxt, 0x130) = PTR(s2, 0x130);
            } else {
                PTR(arg1, 0) = PTR(s2, 0x130);
            }
            if (PTR(s2, 0x130) != NULL) {
                PTR(PTR(s2, 0x130), 0x134) = PTR(s2, 0x134);
            } else {
                PTR(arg1, 4) = PTR(s2, 0x134);
            }
            S32(arg1, 0x58) = S32(arg1, 0x58) - 1;
        } else {
            s3 = arg0 + S32(s2, 4) * 0x88 + 4;
            t2 = 0;
            do {
                idx = S32(s2, 4);
                base = (u8 *)sp[idx] + t2 * 16;
                e = t2 * 16 + 0xB0;
                F32(s2, e) = F32(base, 0) * F32(s2, 0x20);
                S32(s2, e + 4) = 0;
                F32(s2, e + 8) = F32(base, 8) * F32(s2, 0x1C);
                F32(s2, e + 0xC) = 1.0f;
                t2++;
            } while (t2 < 4);

            s1 = s2 + 0x60;
            s0 = s2 + 0x40;
            /* a3 is the loop's final (t2 < 4) == 0 */
            func_0012A360(F32(s2, 0x34), s0, s1, s0, 0);
            Vec3_Add(s2 + 0x50, s0, arg2 + 0x10);
            F32(s2, 0x5C) = 1.0f;
            Vec3_Add(s1, s1, s2 + 0xA0);
            Vec3_Normalize(s1, s1);

            v1 = S32(s2, 0);
            if (!(v1 & 2) && (F32(s3, 0x74) <= F32(s2, 0xC))) {
                F32(s2, 0x9C) = 0.0f;
                v1 = v1 | 2;
                S32(s2, 0) = v1;
            }
            if ((v1 & 4) == 0) {
                if (F32(s2, 0x18) <= F32(s2, 0xC)) {
                    v1 = v1 | 4;
                    S32(s2, 0) = v1;
                    F32(s2, 0x9C) = -F32(s2, 0x8C) / (F32(s2, 0x10) - F32(s2, 0xC));
                }
            }

            s0 = s2 + 0x80;
            if ((v1 & 0x10) == 0 && F32(s2, 0x14) <= F32(s2, 0xC)) {
                f20 = F32(s2, 0x10) - F32(s2, 0xC);

                r = (f32)rand() / D_003851B0;
                F32(s2, 0x38) = ((F32(s3, 0x3C) + F32(s3, 0x40) * r) * F32(arg2, 0xC) - F32(s2, 0x34)) / f20;

                r = (f32)rand() / D_003851B0;
                F32(s2, 0x24) = ((F32(s3, 0x6C) + F32(s3, 0x70) * r) * F32(arg2, 0xC) - F32(s2, 0x1C)) / f20;

                r = (f32)rand() / D_003851B0;
                S32(s2, 0) = S32(s2, 0) | 0x10;
                F32(s2, 0x28) = ((F32(s3, 0x54) + F32(s3, 0x58) * r) * F32(arg2, 0xC) - F32(s2, 0x20)) / f20;

                s0 = s2 + 0x80;
            }
            func_00129B28(s0, s0, s2 + 0x90);
            func_00129D68(s0, s0, 0.0f, 255.0f);

            f0 = F32(s2, 0x20) + F32(s2, 0x28);
            F32(s2, 0x20) = f0;
            F32(s2, 0x34) = F32(s2, 0x34) + F32(s2, 0x38);
            if (f0 < 0.0f) {
                F32(s2, 0x20) = 0.0f;
            }
            f1 = F32(s2, 0x1C) + F32(s2, 0x24);
            F32(s2, 0x1C) = f1;
            if (f1 < 0.0f) {
                F32(s2, 0x1C) = 0.0f;
            }
            F32(s2, 0xC) = F32(s2, 0xC) + 1.0f;
        }
        nxt = PTR(s2, 0x130);
        s2 = nxt;
    } while (s2 != NULL);
}
