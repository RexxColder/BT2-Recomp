#include "m2c_macros.h"

extern s32 D_00388D4C __attribute__((section(".data")));

s32 func_00262440(s32 arg0) {
    return D_00388D4C + ((arg0 & 0xFFFF) * 0x30);
}
