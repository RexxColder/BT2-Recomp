#include "common.h"

void func_002F9300(s32 arg0);
extern u8 D_0037D170[] __attribute__((section(".data")));
extern u8 D_0039D93C[] __attribute__((section(".data")));

void func_002F96C0(s32 arg0) {
    s32 s0;
    s32 s1;
    s32 s3;
    s32 s4;
    s32 a1;

    if (arg0 == 0) {
        func_002F9300((s32)D_0037D170);
        return;
    }
    s0 = 0;
    s4 = strlen((char *)arg0);
    s1 = (s32)D_0039D93C;
    a1 = s1;
    do {
        s1 += 0x10;
        s3 = s0 * 0x10;
        s0 += 1;
        if (strncmp((char *)arg0, (char *)a1, s4) == 0) {
            *(u8 *)((s32)D_0039D93C + s3) = 0;
            return;
        }
        a1 = s1;
    } while (s0 < 0x20);
}
