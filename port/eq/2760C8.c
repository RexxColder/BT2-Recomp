#include "common.h"
#include "sys/dma.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
extern u8 D_00376B20[] __attribute__((section(".data")));

/* 0x002760C8: copy the 0x30-byte table D_00376B20 to the stack and hand it to Dma_AddData. */
void func_002760C8(void) {
    u8 buf[0x30];

    memcpy(buf, D_00376B20, 0x30);
    Dma_AddData(buf, 0x30);
}
