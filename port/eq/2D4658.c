#include "common.h"

s32 func_002D45D8(void *arg0);
s32 func_002D4A48(void *arg0, s32 *arg1, s32 *arg2);
s32 memcmp(void *arg0, void *arg1, u32 arg2);
extern u8 D_0037A838[];

s32 func_002D4658(void *arg0, s32 *arg1) {
    s32 sp[2];
    u8 *temp_s1;
    s32 var_v0;

    *arg1 = 0;
    temp_s1 = *(u8 **)((u8 *)arg0 + 4) + 0x20;
    if (func_002D45D8(arg0) != 1) {
        if ((u32)*(s32 *)((u8 *)arg0 + 8) < 0x800U) {
            *(s32 *)arg0 = -1;
            return 0;
        }
        if (memcmp(temp_s1, D_0037A838, 0x18) != 0) {
            *(s32 *)arg0 = -1;
            return 0;
        }
        *(s32 *)arg0 = 2;
        var_v0 = func_002D4A48(arg0, sp, &sp[1]);
        if (var_v0 != 0) {
            var_v0 = 1;
            *(s32 *)((u8 *)arg0 + 0xC) = (sp[0] * 0x64) + sp[1];
            *arg1 = 1;
        }
        return var_v0;
    }
    return 0;
}
