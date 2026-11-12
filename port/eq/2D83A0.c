#include "common.h"

u32 func_002D8278(u8 *arg0, s32 arg1);
s32 strncmp(const char *s1, const char *s2, u32 n);
extern char D_0037AE50[] __attribute__((section(".data")));
extern char D_0037AE58[] __attribute__((section(".data")));

s32 func_002D83A0(char *arg0, s32 arg1) {
    char *s0;
    s32 v;

    if (arg0 == NULL || arg1 < 0) {
        return 0;
    }
    v = 0;
    if (func_002D8278((u8 *)arg0, arg1) >= 2U) {
        s0 = arg0 + 0x15;
        v = 1;
        if (strncmp(s0, D_0037AE50, 1) != 0) {
            v = (strncmp(s0, D_0037AE58, 1) != 0) ? 0 : 2;
        }
    }
    return v;
}
