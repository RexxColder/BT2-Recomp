#include "common.h"

void func_00183AE8(s32 arg0, s32 arg1);
void func_00183B30(s32 arg0, s32 arg1);
void func_0025E0B8(s32 arg0, s32 arg1, s32 arg2);
void func_00261558(s32 arg0, s32 arg1);
s32 func_002623D8(void);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_00387A40;

void func_00183A18(s32 arg0) {
    s32 var_s2;
    s32 var_s0;
    u8 *var_s1;

    var_s2 = arg0;
    var_s1 = (u8 *)(var_s2 + 0xAD8);
    var_s0 = var_s2 + 0xA10;
    memset(var_s1, 0, 0x30);
    *(s32 *)(var_s1 + 0x24) = *(s32 *)(var_s0 + 0x48);
    var_s0 = func_002623D8();
    func_0025E0B8(var_s0, *(s32 *)(D_00387A40 + 8) + (var_s0 * 0x1520), (s32)var_s1);
    *(s32 *)(var_s1 + 0x30) = var_s0;
    func_00183AE8(var_s2, 0);
    func_00261558(var_s0 & 0xFFFF, 0);
    func_00183B30(var_s2, 0);
}
