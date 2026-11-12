#include "common.h"
#include "sys/dma.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
extern u8 D_0036C658[] __attribute__((section(".data")));

/* 0x0010C9E0: copy the 0x30-byte table D_0036C658 to the stack and hand it to Dma_AddData. */
void func_0010C9E0(void) {
    u8 buf[0x30];

    memcpy(buf, D_0036C658, 0x30);
    Dma_AddData(buf, 0x30);
}
