#include "common.h"

s32 BtlTask_SetDead(s32 arg0);
void func_001C8CB8(s32 arg0);
void func_001C8F00(s32 arg0);
void func_001C9108(s32 arg0);
s32 func_001C91F0(s32 arg0);
void func_001C9278(s32 arg0, s32 arg1);
void func_001C92E8(s32 arg0, s32 arg1);

void func_001C8AD8(u8 *arg0) {
    u8 *s0;
    u8 st;
    s32 t;
    s32 flags;

    st = *(u8 *)(arg0 + 1);
    s0 = *(u8 **)(arg0 + 0x38);

    if (st == 1) {
        *(u8 *)(arg0 + 1) = 2;
    } else if (st == 0) {
        func_001C8F00(1);
        *(u8 *)(arg0 + 1) = *(u8 *)(arg0 + 1) + 1;
    } else if (st == 2) {
        t = func_001C91F0((s32)arg0);
        if (t == 0) {
            *(s32 *)(s0 + 0x94) = *(s32 *)(s0 + 0x94) | 2;
        }
        if (*(s32 *)(s0 + 0x94) & 2) {
            if (t != 0) {
                func_001C9278((s32)arg0, t);
            }
            *(u8 *)(arg0 + 1) = *(u8 *)(arg0 + 1) + 1;
        }
    }

    flags = *(s32 *)(s0 + 0x94);
    if (!(flags & 4)) {
        func_001C8CB8((s32)arg0);
        func_001C9108((s32)arg0);
        flags = *(s32 *)(s0 + 0x94);
        t = func_001C91F0((s32)arg0);
        if (t == 0 && !(flags & 2)) {
            flags = flags | 2;
            *(s32 *)(s0 + 0x94) = flags;
        }
        if (!(flags & 4)) {
            return;
        }
    }
    func_001C92E8((s32)arg0, *(s32 *)(s0 + 0x90));
    BtlTask_SetDead((s32)arg0);
}
