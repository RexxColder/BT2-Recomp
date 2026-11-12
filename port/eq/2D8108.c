#include "common.h"

char *strncpy(char *d, const char *s, u32 n);
char *strcat(char *d, const char *s);
s32 func_00325830(char *arg0, const char *arg1, s32 arg2);
void func_002D8198(char *arg0, s32 arg1);
extern char D_0037ADF8[] __attribute__((section(".data")));
extern char D_0037AE08[] __attribute__((section(".data")));
extern char D_0037AE10[] __attribute__((section(".data")));
extern char D_0037AE18[] __attribute__((section(".data")));

void func_002D8108(char *arg0, s32 arg1) {
    char buf[0x20];
    char *s0;

    strncpy(arg0, D_0037ADF8, 8);
    func_00325830(buf, D_0037AE08, 0x13);
    s0 = arg0 + 0x10;
    strcat(arg0, buf);
    strncpy(s0, D_0037AE10, 2);
    func_002D8198(s0, arg1);
    strcat(s0, D_0037AE18);
}
