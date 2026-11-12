#include "common.h"

u8 *func_002A3DB8(s32 arg0);
void func_002A4EB0(s32 arg0, s32 arg1) {
    u8 *p = func_002A3DB8(arg0);
    *(u8 *)(p + 0x18) = (u8)arg1;
}
