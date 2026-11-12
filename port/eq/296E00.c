#include "common.h"

s32 func_003126C8(s32 arg0, s32 arg1);
s32 sceVu0CopyMatrix(s32 arg0, s32 arg1);

void func_00296E00(u8 *arg0) {
    *(s32 *)(arg0 + 0x4) = *(s32 *)(arg0 + 0x0);
    func_003126C8((s32)(arg0 + 0xF0), (s32)(arg0 + 0x40));
    sceVu0CopyMatrix((s32)(arg0 + 0x100), (s32)(arg0 + 0x50));
    *(s64 *)(arg0 + 0x210) = 0;
    *(s32 *)(arg0 + 0x0) = *(u8 *)(arg0 + 0x0);
}
