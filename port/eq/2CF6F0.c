#include "common.h"

void func_002CF760(u8 *arg0);
void func_002DA708(u8 *arg0, s32 arg1, s32 arg2);

void func_002CF6F0(u8 *arg0) {
    func_002DA708(arg0, 0, 0x376);
    func_002CF760(arg0);
    *(s32 *)(arg0 + 0xDA8) = 0;
    *(s32 *)(arg0 + 0xDD4) = -1;
    *(s32 *)(arg0 + 0xDC8) = -8;
    *(s32 *)(arg0 + 0xDCC) = 1;
    *(s32 *)(arg0 + 0xDAC) = 0;
    *(s32 *)(arg0 + 0xDB0) = -8;
    *(s32 *)(arg0 + 0xDB4) = 1;
    *(s32 *)(arg0 + 0xDB8) = -1;
    *(s32 *)(arg0 + 0xDBC) = -1;
    *(s32 *)(arg0 + 0xDC0) = 0;
    *(s32 *)(arg0 + 0xDC4) = 0;
    *(s32 *)(arg0 + 0xDD0) = 0;
}
