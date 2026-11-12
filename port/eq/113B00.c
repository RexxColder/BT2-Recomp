#include "common.h"

void func_00113B00(u8 *arg0, s32 arg1, s32 arg2) {
    if (*(s32 *)(arg0 + 0) & 1) {
        *(u16 *)(arg0 + 4) = (u16)(*(u16 *)(arg0 + 4) + arg1);
        *(u16 *)(arg0 + 8) = (u16)(*(u16 *)(arg0 + 8) + arg1);
        *(u16 *)(arg0 + 0xA) = (u16)(*(u16 *)(arg0 + 0xA) + arg2);
        *(u16 *)(arg0 + 6) = (u16)(*(u16 *)(arg0 + 6) + arg2);
    }
}
