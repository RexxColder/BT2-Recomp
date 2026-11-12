#include "common.h"
#include "sys/dma.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
extern u8 D_00376AF0[] __attribute__((section(".data")));

/* 0x00276040: copy the 0x30-byte table D_00376AF0 to the stack and hand it to Dma_AddData. */
void func_00276040(void) {
    u8 buf[0x30];

    memcpy(buf, D_00376AF0, 0x30);
    Dma_AddData(buf, 0x30);
}
