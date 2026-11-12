#include "common.h"

s32 BtlPool_GetCurrent(s32 arg0);
void BtlPool_Free(s32 arg0, u8 *arg1);
void func_001F4278(s32 arg0);
void func_002837C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283800(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 *D_00387920;
extern s32 D_0038792C;

void func_001F4858(s32 arg0) {
    *(s32 *)(D_00387920 + 0x44) = *(s32 *)(D_00387920 + 0x44) | 2;
    BtlPool_Free(BtlPool_GetCurrent(arg0), D_00387920);
    D_00387920 = NULL;
    func_001F4278(0);
    D_0038792C &= ~2;
    func_002837C0(0, 0x80, 0x80, 0x80, 0);
    func_00283800(0, 0x80, 0x80, 0x80, 0);
    func_00283840(0, 0x80, 0x80, 0x80, 0);
}
