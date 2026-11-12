#include "common.h"

/* GUESS arity: the asm passes a0 (arg0) and a1 (arg1) through to both calls; ctx.h says 0 */
void func_002E93C0(s32 arg0, s32 arg1);
void func_002E93D8(s32 arg0, s32 arg1);

s32 func_002F1400(u8 *arg0, s32 arg1) {
    func_002E93C0((s32)arg0, arg1);
    if (arg1 <= 0) {
        *(s32 *)(arg0 + 0xA4) = *(s32 *)(arg0 + 0xA4) - arg1;
    } else {
        *(s32 *)(arg0 + 0xA0) = *(s32 *)(arg0 + 0xA0) + arg1;
    }
    func_002E93D8((s32)arg0, arg1);
    return arg1;
}
