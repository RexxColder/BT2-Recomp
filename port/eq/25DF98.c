#include "common.h"

void func_0025D0A8(u8 *arg0);
void func_0025CD70(s32 arg0);
void func_0025DC38(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_0025DF98(s32 arg0, u8 *arg1, u8 *arg2) {
    u8 *temp_s1;
    s32 v;

    func_0025D0A8(arg1);
    func_0025CD70(*(s32 *)(arg1 + 0xAF0 + 4));
    temp_s1 = *(u8 **)(arg1 + 0xE90);
    if (temp_s1 != NULL) {
        *(s8 *)(temp_s1 + 0xC) = 0;
    }
    memset(arg1, 0, 0x18580);
    func_0025DC38(arg0, arg1, arg2, 1);
    *(s32 *)(arg1 + 4) = *(u8 *)(*(u8 **)(arg1 + 0x958) + 0x3D);
    v = (s32)((u32)*(s32 *)(arg2 + 0xC) + 0xFFFF5345U);
    *(s32 *)(arg1 + 8) = v % 9;
}
