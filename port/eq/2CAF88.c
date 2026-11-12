#include "common.h"

void func_002C32B0(s32 *arg0);
void func_002C32C8(s32 *arg0);
void func_002CB140(u8 *arg0, u8 **arg1, u8 **arg2);
s32 func_002D07B0(u8 *arg0, s32 arg1);
s32 func_002D2268(u8 *arg0, s32 arg1, s32 arg2);

void *func_002CAF88(u8 *arg0) {
    s32 sp[1];
    u8 *sp4;
    u8 *sp8;
    s32 var_s1;
    u8 *var_s0;

    var_s0 = arg0;
    func_002C32B0(sp);
    func_002CB140(var_s0, &sp4, &sp8);
    sp8 = ((*(s32 *)(var_s0 + 0x48) ^ 4) != 0) ? NULL : sp8;
    var_s1 = func_002D07B0(var_s0, 0xF);
    if (sp4 == NULL) {
        var_s0 = NULL;
    } else if (var_s1 != 0 && func_002D2268(var_s0, *(s32 *)(sp4 + 0x38), *(s32 *)(sp4 + 0x3C)) == 0) {
        var_s0 = NULL;
    } else {
        if (sp8 == NULL) {
            var_s0 = (u8 *)1;
        } else if (var_s1 != 0 && func_002D2268(var_s0, *(s32 *)(sp8 + 0x38), *(s32 *)(sp8 + 0x3C)) == 0) {
            var_s0 = (u8 *)1;
        } else {
            var_s0 = (u8 *)2;
        }
    }
    func_002C32C8(sp);
    return var_s0;
}
