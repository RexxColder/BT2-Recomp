#include "common.h"

s32 StgRigid_GetSphere(s32 arg0);
void ColBounds_OfSphere(s32 arg0, s32 arg1, s32 arg2);
s32 ColBox_Overlaps(s32 arg0, s32 arg1);
void ColSphere_Set(f32 farg0, s32 arg0, s32 arg1);
s32 ColSphere_TestSphere(s32 arg0, s32 arg1);
s32 ColSphere_ContactObb(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 *D_00387A40;

s32 func_00242040(u8 *arg0) {
    s32 sp[8];
    s64 sp20[4];
    u8 sp40[0x20];
    u8 sp60[0x10];
    u8 sp70[0x10];
    u8 sp80[0x10];
    u8 *sph;
    u8 *p;
    s32 s0;
    s32 s3;
    s32 s4;
    s32 flags;

    sph = (u8 *)StgRigid_GetSphere(*(s32 *)(arg0 + 0xC));
    if (sph == NULL) {
        return (s32)sph;
    }

    sp20[0] = *(s64 *)(sph + 0x00);
    s3 = 0;
    s4 = 0;
    sp20[1] = *(s64 *)(sph + 0x08);
    sp20[2] = *(s64 *)(sph + 0x10);
    sp20[3] = *(s64 *)(sph + 0x18);
    ColBounds_OfSphere((s32)sp40, (s32)sp20, (s32)sph);

    for (;;) {
        s0 = *D_00387A40 + s4;
        if (ColBox_Overlaps((s32)sp40, s0 + 0xF60) != 0) {
            ColSphere_Set(5.0f, (s32)sp, s0 + 0x9C0);
            if (ColSphere_TestSphere((s32)sp20, (s32)sp) != 0) {
                return s3;
            }
            p = *(u8 **)(s0 + 0xEF0);
            for (;;) {
                if (ColSphere_ContactObb((s32)sp20, (s32)(p + 0x40), (s32)sp60, (s32)sp70, (s32)sp80) != 0) {
                    return s3;
                }
                flags = *(s32 *)p;
                p += 0x1D0;
                if (flags & 1) {
                    break;
                }
            }
        }
        s3 += 1;
        s4 += 0x18580;
        if (s3 >= 2) {
            return -1;
        }
    }
}
