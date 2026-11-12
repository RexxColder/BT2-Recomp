#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 func_001272E0(void);
s32 func_00127480(s32 arg0, s32 arg1);
s32 func_0011C288(s32 arg0, s32 arg1, s32 arg2);
void func_0011C4C8(s32 arg0);
s32 func_001275A0(s32 arg0);
void EftHit_SetTaskFlag(s32 arg0, s32 arg1, s32 arg2);
void func_001279F8(s32 arg0, s32 arg1);
void func_0020D048(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_0020D240(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);

extern f32 D_00384068;
extern f32 D_0038406C;

/* 0x0011C588: per-frame update of the object's entries (0x180 bytes each, count at +0x6000 of the object from
 * func_001272E0). An entry is handled when func_00127480 accepts it: a flag from its +0x64 record and +0xC
 * drive func_0011C288; on success the entry is hit-tested (func_001275A0) and, when its +0xC word is 1, two
 * float updates are applied to its +0x20 block. */
void func_0011C588(void) {
    s32 obj;
    s32 i;
    s32 s1;
    s32 count;
    s32 x;
    s32 v1;
    s32 a2;
    s32 a1;

    obj = func_001272E0();
    count = LD32(obj, 0x6000);
    if (count <= 0) {
        return;
    }

    i = 0;
    s1 = obj;
    do {
        if (func_00127480(s1, 0) != 0) {
            a2 = 0;
            x = LD32(s1, 0x64);
            if (x != 0) {
                v1 = LD32(x, 0x20);
                if (LD32(v1, 0x4) != 0) {
                    a2 = (LD32(v1, 0x8) == 7);
                } else {
                    a2 = (LD32(v1, 0x8) == 4);
                }
            }
            a1 = (LD32(s1, 0xC) == 0);
            if (func_0011C288(s1 + 0x70, a1, a2) != 0) {
                if (func_001275A0(s1) != 0) {
                    EftHit_SetTaskFlag(i, 4, s1 + 0xA0);
                    func_001279F8(i, s1 + 0xB0);
                    func_0011C4C8(s1);
                    if (LD32(s1, 0xC) == 1) {
                        func_0020D048(s1 + 0x20, 100.0f, D_00384068, 3.0f, 0.5f);
                        func_0020D240(s1 + 0x20, 100.0f, 1000.0f, 1.0f, D_0038406C);
                    }
                }
            }
        }
        i++;
        count = LD32(obj, 0x6000);
        s1 += 0x180;
    } while (i < count);
}
