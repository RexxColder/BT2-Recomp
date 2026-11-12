#include "common.h"

void func_00101408(void);
void func_002979F0(s32 arg0);

extern u8 *D_00387F2C;

void func_0024B4C8(void) {
    func_00101408();
    func_002979F0(*(s32 *)(D_00387F2C + 0x10A4) ^ 1);
}
