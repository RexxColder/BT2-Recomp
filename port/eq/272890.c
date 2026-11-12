#include "common.h"

#define PTR(v) ((u8 *)(s32)(v))
#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define LD16(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define LDF(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern s32 D_00387AB4;
extern u8 *D_003876A0;
extern u8 *gBtlStage;

s32 func_002745F8(s32 arg0);
s32 StgOfsTable_Get(s32 arg0, s32 arg1);

/* 0x00272890: per-frame step over the records of the current stage (16 bytes each, after the table at
 * stage+4 indexed by stage+0xC): records with a positive count get their float at +4 flags tested, the
 * float at +0x20 is raised by 2.0 and clamped to 0 when the table entry's u16 is below it. */
void func_00272890(void) {
    s32 i;
    s32 v1;
    s32 s0;
    s32 vv;
    s32 tab;
    u8 *s1;
    u8 *s2;
    u8 *p;

    if (D_00387AB4 == 0) {
        return;
    }
    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }

    s2 = PTR(LD32(gBtlStage, 4));
    v1 = LD16(s2, 6);
    if (v1 == 0) {
        return;
    }
    s1 = s2 + LD32(s2, 0xC) * 4;
    i = 0;
    do {
        s0 = LD32(s1, 8);
        if (s0 > 0) {
            if ((LD32(s1, 4) & 0x40000000) == 0 && func_002745F8(i) != 0) {
                s1 += 0x10;
                v1 = LD16(s2, 6);
            } else {
                vv = LD32(s1, 0xC);
                s1 += 0x10;
                if (vv < 0) {
                    vv += 3;
                }
                vv = (vv >> 2) * 4;
                p = PTR(LD32(gBtlStage, 4)) + vv;
                LDF(p, 0x20) = LDF(p, 0x20) + 2.0f;
                tab = StgOfsTable_Get(D_00387AB4, 3 * s0 - 1);
                if ((f32)LD16(PTR(tab), 0xC) < LDF(p, 0x20)) {
                    LD32(p, 0x20) = 0;
                }
                v1 = LD16(s2, 6);
            }
        } else {
            s1 += 0x10;
        }
        i++;
    } while (i < v1);
}
