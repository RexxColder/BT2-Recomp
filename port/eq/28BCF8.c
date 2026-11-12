#include "common.h"

void sceDbcInit(void);
void scePad2Init(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
s32 scePad2CreateSocket(s32 *arg0, u8 *arg1);
extern u8 D_003B0B00[] __attribute__((section(".data")));

void func_0028BCF8(void) {
    s32 sp[8];

    sceDbcInit();
    scePad2Init(0);
    memset(D_003B0B00, 0, 0x300);
    memset(sp, 0, 0x20);
    sp[0] = 2;
    sp[1] = 0;
    sp[2] = 0;
    *(s32 *)(D_003B0B00 + 0x100) = scePad2CreateSocket(sp, D_003B0B00);
    memset(sp, 0, 0x20);
    sp[0] = 2;
    sp[1] = 1;
    sp[2] = 0;
    *(s32 *)(D_003B0B00 + 0x280) = scePad2CreateSocket(sp, D_003B0B00 + 0x180);
}
