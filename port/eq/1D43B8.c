#include "common.h"

s32 BtlScene_IsTimeStopped(void);
void func_001D4518(s32 arg0, s32 arg1, s32 arg2);
void func_001D45B8(s32 arg0, s32 arg1, s32 arg2);
void func_001D1B90(f32 farg0, s32 arg0);
f32 func_00208670(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_00387E9C;

void func_001D43B8(void) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 a0;
    s32 rec;
    s32 off;
    s32 tv;
    u8 a1;

    if (BtlScene_IsTimeStopped() == 0) {
        s2 = 0;
        s1 = 0;
        do {
            a0 = s1 + *(s32 *)(D_00387E9C + 0x1400);
            a1 = *(u8 *)(a0 + 8);
            s0 = 0;
            if (a1 == 2) {
                func_001D4518(a0, a1, (s32)D_00387E9C);
            } else if (a1 == 3) {
                func_001D45B8(a0, a1, (s32)D_00387E9C);
            }
            a0 = *(s32 *)(D_00387E9C + 0x1400);
            do {
                rec = s1 + a0;
                if (*(s32 *)(rec + 0xC) & (1 << s0)) {
                    off = (s0 * 4) + 0x10;
                    *(f32 *)(rec + off) = *(f32 *)(rec + off) - 1.0f;
                    tv = s1 + *(s32 *)(D_00387E9C + 0x1400);
                    if ((*(f32 *)(tv + off) <= 0.0f) && (s0 == 0)) {
                        func_001D1B90(func_00208670(*(s32 *)tv, rec, (s32)D_00387E9C), *(s32 *)tv);
                        tv = s1 + *(s32 *)(D_00387E9C + 0x1400);
                        *(s32 *)(tv + 0xC) = *(s32 *)(tv + 0xC) & ~1;
                    }
                }
                s0 += 1;
                a0 = *(s32 *)(D_00387E9C + 0x1400);
            } while (s0 <= 0);
            s2 += 1;
            s1 += 0x14;
        } while (s2 < 2);
    }
}
