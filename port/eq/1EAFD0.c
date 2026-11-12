#include "common.h"

/* GUESS arity: func_00129C28 gets (t+0x80, copy, arg0) from the asm; ctx.h says 2 */
void func_00129C28(s32 arg0, s32 arg1, s32 arg2);
extern u8 func_001E9428[] __attribute__((section(".data")));

#ifdef __mips__
#define STEAM_IS_UPDATE(p) ((void *)(p) == (void *)func_001E9428)
#else
#define STEAM_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001E9428u)
#endif

void func_001EAFD0(u8 *arg0, void *arg1) {
    s64 sp[2];
    u8 *t;

    sp[0] = ((s64 *)arg1)[0];
    sp[1] = ((s64 *)arg1)[1];
    if (arg0 != NULL && STEAM_IS_UPDATE(*(void **)*(u8 **)(arg0 + 0x28))) {
        t = *(u8 **)(arg0 + 0x38);
        if ((*(u16 *)(t + 0x124) & 1) != 0) {
            func_00129C28((s32)(t + 0x90), (s32)sp, (s32)arg0);
        }
    }
}
