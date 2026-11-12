#include "common.h"

void func_002978A8(s32 arg0);

extern u8 *D_00387ED0;

void func_00297A30(s32 arg0) {
    func_002978A8(arg0);
    *(s32 *)(D_00387ED0 + 0x64) = -1;
    *(s32 *)(D_00387ED0 + 0x70) = 0;
}
