#include "common.h"

extern u8 D_003B0F7C[] __attribute__((section(".data")));
u8 *func_002A3E80(s32 arg0) {
    return D_003B0F7C + arg0 * 0x68;
}
