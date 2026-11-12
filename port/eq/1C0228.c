#include "common.h"

void func_00129C28(s32 *arg0, u8 *arg1);
void func_001BFC00(f32 farg0, f32 farg1, s32 arg2, u8 *arg3, s32 *arg4, s64 arg5);

void func_001C0228(s32 arg0, u8 *arg1, u8 *arg2) {
    s32 sp[4];
    u8 *s0;
    f32 fv;

    func_00129C28(sp, arg2 + 0x70);
    s0 = *(u8 **)(arg2 + 0xE8);
    if (s0 == NULL) {
        return;
    }
    do {
        fv = *(f32 *)(arg2 + 0x28);
        func_001BFC00(fv, fv, arg0, s0, sp,
                      *(s64 *)(*(u8 **)(arg1 + 0x34) + *(s32 *)(arg1 + 0x30) * 0x10));
        s0 = *(u8 **)(s0 + 0xF0);
    } while (s0 != NULL);
}
