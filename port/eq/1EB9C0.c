#include "common.h"

extern s32 func_001EB270();
extern s32 func_00129C28(u8 *p, s32 a1);

#ifdef __mips__
#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)func_001EB270)
#else
#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
#endif

/* 0x001EB9C0: if obj's vtable entry is func_001EB270 and obj->+0x38 has bit 0 of +0x60: tail call func_00129C28(sub + 0x20, a1). */
s32 func_001EB9C0(u8 *obj, s32 a1) {
    u8 *sub;

    if (obj == 0) {
        return 0;
    }
    if (!LOOP_IS_UPDATE(*(void **)*(u8 **)(obj + 0x28))) {
        return 0;
    }
    sub = *(u8 **)(obj + 0x38);
    if (sub == 0) {
        return 0;
    }
    if ((*(u16 *)(sub + 0x60) & 1) == 0) {
        return 0;
    }
    return func_00129C28(sub + 0x20, a1);
}
