#include "common.h"
extern u8 D_003B1FF0[] __attribute__((section(".data")));

u8 *func_002A3DB8(s32 arg0) {
    return D_003B1FF0 + arg0 * 0x28;
}
