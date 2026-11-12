#include "common.h"

void func_002EA050(void *arg0);
void func_002F44A0(void *arg0, void *arg1, s32 arg2, s32 arg3);
void func_002F6838(void *arg0, s32 arg1);
char *strcpy(char *dst, const char *src);
extern u8 D_0037CEF8[] __attribute__((section(".data")));

void func_002F71E8(u8 *arg0, char *arg1, s32 arg2, s32 arg3) {
    if (arg0 == NULL || arg1 == NULL) {
        func_002EA050(D_0037CEF8);
        return;
    }
    func_002F44A0(arg0, arg1, arg2, arg3);
    strcpy(*(char **)(arg0 + 0xB0), arg1);
    *(s32 *)(arg0 + 0xBC) = arg2;
    *(s32 *)(arg0 + 0xC0) = arg3;
    *(s32 *)(arg0 + 0xB4) = (s32)*(char **)(arg0 + 0xB0);
    *(u8 *)(arg0 + 0xAC) = 1;
    *(s32 *)(arg0 + 0xB8) = 0;
    *(u8 *)(arg0 + 1) = 1;
    *(u8 *)(arg0 + 2) = 0;
    func_002F6838(arg0, 0);
}
