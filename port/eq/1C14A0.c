#include "common.h"

/* GUESS arity: F1EBC80 gets the pool pointer plus 0x20D48, then the own second and fifth arguments, and the
 * third and fourth arguments shifted left by 16. */
void *func_001EBC80(void *a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern u8 *D_00387898;

void *func_001C14A0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *base;
    u8 *p;
    s16 s4;
    s16 s1;
    u8 s2;
    s32 idx;

    s4 = (s16)arg2;
    s1 = (s16)arg3;
    s2 = (u8)arg4;
    if (*(u8 *)((u8 *)arg0 + 0xD0) >= 0x28) {
        return NULL;
    }
    base = *(u8 **)(*(u8 **)(D_00387898 + 4) + 0x38);
    p = func_001EBC80(base + 0x20D48, arg1, (s32)((u32)arg2 << 16), (s32)((u32)arg3 << 16), arg4);
    if (p == NULL) {
        return NULL;
    }
    idx = *(u8 *)((u8 *)arg0 + 0xD0);
    *(void **)((u8 *)arg0 + 0x30 + 4 * idx) = p;
    *(u8 *)((u8 *)arg0 + 0xD0) = (u8)(*(u8 *)((u8 *)arg0 + 0xD0) + 1);
    *(s16 *)((u8 *)p + 6) = s1;
    *(u8 *)p = s2;
    *(s32 *)((u8 *)p + 8) = arg1;
    *(s16 *)((u8 *)p + 4) = s4;
    return p;
}
