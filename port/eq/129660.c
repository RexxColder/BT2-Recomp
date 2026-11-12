#include "common.h"
#include "sys/dma.h"

void func_00129660(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    *(s128 *)(arg0 + 0) = *(s128 *)arg1;
    *(s128 *)(arg0 + 0x10) = *(s128 *)arg2;
    *(s128 *)(arg0 + 0x20) = *(s128 *)arg3;
}
