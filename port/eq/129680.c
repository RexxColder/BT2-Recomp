#include "common.h"
#include "sys/dma.h"

void func_00129680(u8 *arg0, u8 *arg1) {
    *(s128 *)(arg0 + 0) = *(s128 *)(arg1 + 0);
    *(s128 *)(arg0 + 0x10) = *(s128 *)(arg1 + 0x10);
    *(s128 *)(arg0 + 0x20) = *(s128 *)(arg1 + 0x20);
}
