#include "common.h"

void Mtx_StoreIdentity(s32 arg0);
void func_002088F0(s32 arg0, s32 arg1);
void Mtx_RotateZXY(s32 arg0, s32 arg1, s32 arg2);
void func_00129C50(s32 arg0, s32 arg1, s32 arg2);
void func_001CD498(s32 arg0, s32 arg1, s32 arg2);
void func_001CDA98(s32 arg0, s32 arg1, s32 arg2);
void func_001CD958(s32 arg0);
void func_001CD7B0(s32 arg0);

void func_001CD328(u8 *arg0) {
    s32 buf[20];
    u8 *s1;
    u8 *s0;
    u8 *s2;
    u8 *s4;
    s32 idx;
    s32 s3;
    s32 s5;

    s5 = 0;
    s1 = *(u8 **)(arg0 + 0x38);
    Mtx_StoreIdentity((s32)buf);
    s4 = s1;
    func_002088F0(*(s32 *)(s1 + 0x110), (s32)&buf[16]);
    Mtx_RotateZXY((s32)buf, (s32)buf, (s32)&buf[16]);
    func_00129C50((s32)(s1 + 0x100), (s32)buf, (s32)(s1 + 0x100));
    do {
        s2 = s4 + 0xC0;
        s3 = 1;
        s0 = *(u8 **)(s1 + 0x124);
        do {
            idx = 0;
            if (s0 != NULL) {
                idx = *(s32 *)s0;
            }
            func_001CD498((s32)(s1 + (idx * 0x10) + 0x20), (s32)s2, *(s32 *)(s1 + 0x110));
            s2 += 0x10;
            if (s0 != NULL) {
                *(s16 *)(s0 + 4) = 0;
                func_001CDA98((s32)(s1 + 0x124), (s32)(s1 + 0x128), (s32)s0);
                *(s32 *)(s1 + 0x118) = *(s32 *)(s1 + 0x118) - 1;
            }
            s3 -= 1;
            if (s3 >= 0) {
                s0 = *(u8 **)(s1 + 0x124);
            }
        } while (s3 >= 0);
        s5 += 1;
        s4 += 0x20;
    } while (s5 < 2);
    func_001CD958((s32)arg0);
    func_001CD7B0((s32)arg0);
    *(f32 *)(s1 + 0x11C) = *(f32 *)(s1 + 0x11C) + 1.0f;
}
