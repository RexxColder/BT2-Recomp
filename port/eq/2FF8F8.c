#include "common.h"

char *strcpy(char *dst, const char *src);
extern u8 D_00356FB8[] __attribute__((section(".data")));
extern u8 D_0037E820[] __attribute__((section(".data")));

/* 0x002FF8F8(s): with s == NULL, the 6 bytes at D_0037E820 are copied to D_00356FB8; otherwise strcpy(D_00356FB8, s). */
void func_002FF8F8(char *arg0) {
    s32 k;

    if (arg0 == 0) {
        for (k = 0; k < 6; k++) {
            D_00356FB8[k] = D_0037E820[k];
        }
        return;
    }
    strcpy((char *)D_00356FB8, arg0);
}
