#include "common.h"

void func_001EAE78(s32 arg0, s32 arg1);
extern void func_001EB270(void);

#ifdef __mips__
#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)func_001EB270)
#else
#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
#endif

void func_001EB930(u8 *arg0, s32 arg1) {
    u8 *t;
    u8 *p;

    if (arg0 == NULL) {
        return;
    }
    if (!LOOP_IS_UPDATE(*(void **)*(u8 **)(arg0 + 0x28))) {
        return;
    }
    t = *(u8 **)(arg0 + 0x38);
    if (t == NULL) {
        return;
    }
    if ((*(u16 *)(t + 0x60) & 1) == 0) {
        return;
    }
    p = *(u8 **)(t + 0x64);
    if (p == NULL) {
        return;
    }
    do {
        func_001EAE78(*(s32 *)p, arg1);
        p = *(u8 **)(p + 0x08);
    } while (p != NULL);
}
