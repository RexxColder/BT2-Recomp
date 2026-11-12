#include "common.h"

s32 func_002FECA8(s32 arg0);
s32 func_002FED18(s32 arg0);
s32 strcat(s32 arg0, s32 arg1);
s32 strcpy(s32 arg0, s32 arg1);
s32 strlen(s32 arg0);
extern s8 D_00356EB0 __attribute__((section(".data")));
extern s8 D_00356FB8 __attribute__((section(".data")));
extern s8 D_0037E670 __attribute__((section(".data")));

void func_002FED70(s32 arg0, s32 arg1) {
    s32 len;
    s32 i;
    s8 c;

    *(s8 *)arg1 = 0;
    if (func_002FECA8(arg0) == 0) {
        strcpy(arg1, (s32)&D_00356FB8);
    }
    if (func_002FED18(arg1) == 1) {
        strcat(arg1, (s32)&D_00356EB0);
        c = *(s8 *)((s32)&D_00356EB0 + strlen((s32)&D_00356EB0) - 1);
        if (c != 0x5C) {
            if (c != 0x2F && c != 0) {
                c = *(s8 *)arg0;
                if (c != 0x5C) {
                    if (c != 0x2F) {
                        strcat(arg1, (s32)&D_0037E670);
                    }
                }
            }
        }
    }
    strcat(arg1, arg0);
    len = strlen(arg1);
    for (i = 0; i < len; i++) {
        if (*(s8 *)(arg1 + i) == 0x5C) {
            *(s8 *)(arg1 + i) = 0x2F;
        }
    }
}
