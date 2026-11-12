#include "common.h"

s32 BtlKiBlast_GetHitsOf();
f32 BtlKiBlast_GetUnk28Of(s32 arg0);
s32 BtlKiBlast_GetUnk31Of(s32 arg0);
s32 BtlMember_GetActiveGauge(s32 arg0);
s32 BtlObj_GetNodeSide(s32 arg0);
void func_001AE088(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_003126C8(s32 arg0, s32 arg1);
void func_001ADFC0(s32 arg0);

void func_002045B0(void *arg0) {
    u8 *s1;
    s32 s0;
    s32 g;
    s32 side;
    s32 r31;
    s32 v1;
    s32 sp[8];
    f32 f0;

    s1 = (u8 *)arg0;
    if (!(*(s64 *)(s1 + 0x338) & 0x80000)) {
        return;
    }
    s0 = BtlKiBlast_GetHitsOf((s32)arg0);
    g = BtlMember_GetActiveGauge((s32)arg0);
    if (*(u8 *)(g + 0x2C) != 0) {
        s0 = 7;
    }
    if (s0 == 0x11) {
        return;
    }
    if (s0 == 0x10) {
        side = (BtlObj_GetNodeSide(*(s32 *)(s1 + 0xA20)) != 0);
        r31 = BtlKiBlast_GetUnk31Of((s32)arg0);
        func_001AE088(*(s32 *)(s1 + 0x1534), *(s32 *)(s1 + 0xA20), (r31 != 1), side);
        return;
    }
    if (s0 == 0xE || s0 == 0xF) {
        return;
    }

    func_003126C8((s32)sp, (s32)(s1 + 0xA00));
    v1 = *(s32 *)(s1 + 0xA20);
    *(s32 *)((u8 *)sp + 0x10) = *(s32 *)(s1 + 0x1534);
    *(s32 *)((u8 *)sp + 0x14) = v1;
    *(s32 *)((u8 *)sp + 0x18) = BtlKiBlast_GetUnk31Of((s32)arg0);
    f0 = BtlKiBlast_GetUnk28Of((s32)arg0);
    *(f32 *)((u8 *)sp + 0x1C) = f0;
    v1 = *(s32 *)((u8 *)sp + 0x14);
    if (v1 == 0x15) {
        v1 = 0x1F;
        *(s32 *)((u8 *)sp + 0x14) = 0x1F;
    }
    if (v1 == 0x23) {
        *(s32 *)((u8 *)sp + 0x14) = 0x2D;
    }
    func_001ADFC0((s32)sp);
}
