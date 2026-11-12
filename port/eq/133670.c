#include "common.h"

void *memset(void *dst, s32 c, u32 n);
void func_00132F18(f32 *arg0);
void func_00312638(f32 *arg0, f32 *arg1, f32 *arg2);
void func_00312650(f32 *arg0, void *arg1, f32 *arg2);
void func_00312680(f32 farg0, f32 *arg1, f32 *arg2);
void sceVu0Normalize(f32 *arg0, f32 *arg1);
extern f32 D_00384270;
extern f32 D_00384274;
extern f32 D_00384278;
extern f32 D_0038427C;
extern f32 D_00384280;

s32 func_00133670(f32 *arg0) {
    s32 sp[4];
    f32 sp10;
    f32 *s0;
    f32 *s1;
    f32 *s2;
    f32 *s3;
    f32 f0;
    s32 v0;
    s32 temp;

    s1 = (f32 *)((u8 *)arg0 + 0x10);
    s2 = (f32 *)((u8 *)arg0 + 0x30);
    s3 = (f32 *)((u8 *)arg0 + 0x20);
    memset(sp, 0, 0x10);
    func_00312638(arg0, arg0, s1);
    func_00312680(D_00384270, s1, s1);
    s0 = &sp10;
    func_00312650(s0, sp, arg0);
    sceVu0Normalize(s0, s0);
    func_00312680(D_00384274, s0, s0);
    func_00312638(s1, s1, s0);
    *(s32 *)((u8 *)arg0 + 0x1C) = 0;
    func_00312638(s3, s3, s2);
    *s2 = *s2 + D_00384278;
    v0 = 2;
    do {
        f0 = *s3;
        if (D_0038427C < f0) {
            *s3 = D_00384280;
            f0 = D_00384280;
        }
        if (f0 < D_00384280) {
            *s3 = D_0038427C;
        }
        v0 -= 1;
        s3 += 1;
    } while (v0 >= 0);
    if (*(s32 *)((u8 *)arg0 + 0x50) & 2) {
        temp = *(s32 *)((u8 *)arg0 + 0x40);
        if (temp == 0) {
            return 0;
        }
        temp -= 1;
        *(s32 *)((u8 *)arg0 + 0x40) = temp;
        if (temp == 0) {
            func_00132F18(arg0);
        }
        return 1;
    }
    return 1;
}
