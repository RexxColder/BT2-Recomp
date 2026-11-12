#include "common.h"

u8 *func_00211288(s32 arg0);
s32 BtlMember_GetActiveGauge(s32 arg0);
s32 memset(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
void func_001F5958(s32 arg0);
void func_0025DB98(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00202DC0(s32 arg0);
s32 func_0023F960(s32 arg0, s32 arg1);
s32 func_0023F9B0(s32 arg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
extern u8 D_002C3630 __attribute__((section(".data")));

void func_001F63D8(s32 arg0) {
    u8 *s1;
    u8 *s0;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *pa;
    u8 *pb;
    s32 i;
    s32 t;
    s32 v;
    s32 s0v;

    s1 = func_00211288(arg0);
    s0 = s1 + 0x510;
    s2 = s1 + 0x950;
    s3 = s1 + 0x960;
    s4 = (u8 *)BtlMember_GetActiveGauge((s32)s1);
    memset((s32)s0, 0, 0xE0);
    func_003126C8((s32)s0, (s32)s2);
    func_003126C8((s32)(s1 + 0x520), (s32)s3);
    func_003126C8((s32)(*(u8 **)(s1 + 0x1530) + 0x9A0), (s32)s2);
    func_003126C8((s32)(*(u8 **)(s1 + 0x1530) + 0x9B0), (s32)s3);
    func_003126C8((s32)(*(u8 **)(s1 + 0x1530) + 0x9C0), (s32)s2);
    *(f32 *)(s1 + 0x5C4) = *(f32 *)(s1 + 0x524);
    for (i = 0; i < 0xE0; i += 8) {
        *(s64 *)(s1 + 0x5F0 + i) = *(s64 *)(s0 + i);
    }
    for (i = 0; i < 0xE0; i += 8) {
        *(s64 *)(s1 + 0x6D0 + i) = *(s64 *)(s0 + i);
    }
    func_003126C8((s32)s2, (s32)&D_002C3630);
    func_003126C8((s32)s3, (s32)&D_002C3630);
    func_001F5958((s32)s1);
    func_0025DB98(*(s32 *)(s1 + 0x1530));
    func_002113C0((s32)s1, 3, 0x1000, 1);

    pa = (u8 *)(s32)func_00202DC0((s32)s1);
    t = *(s32 *)(*(u8 **)(s1 + 0x1530) + 4);
    *(s32 *)pa = t;
    pb = (u8 *)(s32)func_00202DC0((s32)s1);
    *(s32 *)(pb + 4) = *(s32 *)(*(u8 **)(s1 + 0x1530) + 8);

    s0v = *(s32 *)(s4 + 4);
    t = *(s32 *)(s4 + 8);
    s0v = s0v - t;
    v = func_0023F960((s32)s1, *(s32 *)(s1 + 0x1530));
    s0v = v + s0v;
    *(s32 *)(s4 + 8) = v;
    *(s32 *)(s4 + 0) = s0v;
    *(s32 *)(s4 + 4) = s0v;

    s4 = (u8 *)BtlMember_GetActiveGauge((s32)s1);
    v = func_0023F9B0((s32)s1);
    *(s32 *)(s4 + 0x18) = (s32)((u32)v * 0x186A0u);
    func_002113C0((s32)s1, 0xC, 0x40000, 1);
    BattleSide_SetChara((s32)s1, 0);
}
