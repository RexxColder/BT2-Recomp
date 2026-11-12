#include "common.h"

/* GUESS arity: the tail call passes a0 only on the first path, arity from the draft */
void func_00307028();
char *strncpy(char *arg0, const char *arg1, u32 arg2);
char *strncat(char *arg0, const char *arg1, u32 arg2);
extern s32 (*D_00348C50)(s32 arg0, s32 arg1) __attribute__((section(".data")));
extern s32 D_00348C54 __attribute__((section(".data")));
extern char D_00348C58[] __attribute__((section(".data")));
extern char D_0037BAB8[] __attribute__((section(".data")));

void func_002EA0C8(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg1 == 0)) {
        func_00307028((s32)D_0037BAB8, arg1);
        return;
    }
    strncpy(D_00348C58, (const char *)arg0, 0xFF);
    strncat(D_00348C58, (const char *)arg1, 0xFF);
    if (D_00348C50 != 0) {
        D_00348C50(D_00348C54, (s32)D_00348C58);
    }
    func_00307028((s32)D_00348C58);
}
