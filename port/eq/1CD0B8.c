#include "common.h"

void BtlTask_SetDead(s32 arg0);
void func_001CD328(s32 arg0);
void func_001CD558(s32 arg0);
s32 func_001CD860(s32 arg0);
void func_001CD8E8(s32 arg0);
void func_001CDB40(s32 arg0, s32 arg1);
extern u8 *D_003876A0;

void func_001CD0B8(void *arg0) {
    u8 *s0;
    u8 *s1;
    u16 vv;

    s0 = (u8 *)arg0;
    s1 = *(u8 **)(s0 + 0x38);
    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }

    if (s0[1] == 0) {
        func_001CD558((s32)arg0);
        s0[1] = s0[1] + 1;
    } else if (s0[1] == 1) {
        if (func_001CD860((s32)arg0) == 0) {
            *(u16 *)(s1 + 0x12C) = *(u16 *)(s1 + 0x12C) | 0xA;
        }
        vv = *(u16 *)(s1 + 0x12C);
        if (vv & 2) {
            if (!(vv & 8)) {
                func_001CD8E8((s32)arg0);
            }
            s0[1] = s0[1] + 1;
        }
    }

    vv = *(u16 *)(s1 + 0x12C);
    if (!(vv & 4)) {
        func_001CD328((s32)arg0);
        vv = *(u16 *)(s1 + 0x12C);
        if (func_001CD860((s32)arg0) == 0) {
            if (!(vv & 2)) {
                vv = vv | 0xA;
                *(u16 *)(s1 + 0x12C) = vv;
            }
        }
        if (!(vv & 4)) {
            return;
        }
    }
    func_001CDB40((s32)arg0, *(s32 *)(s1 + 0x110));
    BtlTask_SetDead((s32)arg0);
}
