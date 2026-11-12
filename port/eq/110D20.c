#include "common.h"

extern u8 *D_003876A0;

void *func_0010B078(void);
s32 BtlObjVis_GetView(s32 idx);
void func_00110CA0(void *a, s32 b);
void func_0029D548();
void func_0010D028(void);
void func_0029D580(s32 a);
void func_00113598(void *a);
void func_0010FBA0(void *a, s32 b, s32 c);
void func_0010FFA8(void *a, s32 b, s32 c);
void func_0010D818(void *a, s32 b, s32 c);
void func_0010E268(void *a, s32 b, s32 c);
void func_0010EEA0(void *a, s32 b, s32 c);
void func_001102B0(void *a, s32 b, s32 c);
void func_00110488(void *a, s32 b, s32 c);
void func_00110898(void *a, s32 b, s32 c);
void func_00110B30(void *a, s32 b, s32 c);
f32 sinf(f32 x);

s32 func_00110D20(void) {
    u8 sp[8];
    void *s2;
    s32 s1;
    u8 *s0;
    s32 v1;
    s32 v0;
    s32 a0;
    f32 f20;
    f32 f21;
    f32 t;

    s2 = func_0010B078();
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return 0;
    }

    s1 = 0;
    s0 = (u8 *)s2 + 0xD0;
    a0 = 0;
    do {
        v0 = BtlObjVis_GetView(a0);
        s1 += 1;
        func_00110CA0(s0, v0);
        s0 += 0x750;
        a0 = s1;
    } while (s1 < 2);

    func_0029D548(s1);
    s1 = 0;
    s0 = (u8 *)s2 + 0x818;
    func_0010D028();
    func_0029D580(1);

    /* first loop: s1 = 0, 1 over the records at s2+0x818 */
    do {
        v1 = *(s32 *)s0;
        s0 += 0x750;
        if (v1 >= -0xFF) {
            if (s1 == 1) {
                *(f32 *)(sp + 0) = (f32)(-v1);
            } else {
                *(f32 *)(sp + 0) = (f32)v1;
            }
            *(s32 *)(sp + 4) = 0;
            func_0029D548();
            func_00113598(sp);
            func_0029D548();
            func_0010FBA0(s2, s1, BtlObjVis_GetView(s1));
            func_0010FFA8(s2, s1, BtlObjVis_GetView(s1));
            func_0010D818(s2, s1, BtlObjVis_GetView(s1));
            func_0010E268(s2, s1, BtlObjVis_GetView(s1));
            func_0010EEA0(s2, s1, BtlObjVis_GetView(s1));
            func_0029D580(1);
            func_0029D580(1);
        }
        s1 += 1;
    } while (s1 < 2);

    f21 = 10.0f;
    s1 = 0;
    f20 = -10.0f;
    do {
        s0 = (u8 *)s2 + s1 * 0x750 + 0xD0;
        v1 = *(s32 *)(s0 + 0x730);
        if (v1 >= -0x7F) {
            if (s1 == 1) {
                *(f32 *)(sp + 0) = (f32)(-v1);
            } else {
                *(f32 *)(sp + 0) = (f32)v1;
            }
            *(s32 *)(sp + 4) = 0;
            func_0029D548();
            v0 = *(s32 *)(s0 + 0x73C);
            t = sinf(*(f32 *)(s0 + 0x738));
            if (v0 > 0) {
                t = t * f21;
            } else {
                t = t * f20;
            }
            *(f32 *)(sp + 0) = *(f32 *)(sp + 0) + t;
            func_00113598(sp);
            func_0029D548();
            func_001102B0(s2, s1, BtlObjVis_GetView(s1));
            func_00110488(s2, s1, BtlObjVis_GetView(s1));
            func_00110898(s2, s1, BtlObjVis_GetView(s1));
            func_00110B30(s2, s1, BtlObjVis_GetView(s1));
            func_0029D580(1);
            func_0029D580(1);
        }
        s1 += 1;
    } while (s1 < 2);

    return 0;
}
