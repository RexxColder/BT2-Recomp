#include "common.h"

void func_0025CD70(s32 arg0);
void func_0025D0A8(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

void *func_0025E190(u8 *arg0) {
    u8 *var_s1;

    func_0025D0A8((s32)arg0);
    func_0025CD70(*(s32 *)(arg0 + 0xAF4));
    var_s1 = *(u8 **)(arg0 + 0xE90);
    if (var_s1 != NULL) {
        *(s8 *)(var_s1 + 0xC) = 0;
    }
    return memset(arg0, 0, 0x1520);
}
