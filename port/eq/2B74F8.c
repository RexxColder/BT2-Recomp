#include "common.h"

u32 strlen(u8 *s);
char *strcpy(char *d, const char *s);
char *strncpy(char *d, const char *s, u32 n);
s32 Rand_Range(s32 arg0, s32 arg1);
extern u8 D_00378D58[] __attribute__((section(".data")));

void func_002B74F8(s32 arg0, s32 arg1) {
    if (*(s32 *)(arg0 + 0x1A8) < (s32)strlen((u8 *)arg1)) {
        Rand_Range((s32)D_00378D58, arg1);
        strncpy((char *)*(s32 *)(arg0 + 0x1A4), (const char *)arg1, *(s32 *)(arg0 + 0x1A8));
        return;
    }
    strcpy((char *)*(s32 *)(arg0 + 0x1A4), (const char *)arg1);
}
