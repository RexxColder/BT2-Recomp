#include "common.h"

void func_002EA050(s32 arg0);
s32 func_002F1ED0(s32 arg0);
s64 func_002F2CA0(s32 arg0);
void func_002F32C0(s32 arg0);
extern u8 D_0037C090[] __attribute__((section(".data")));

s64 func_002EC798(s32 arg0) {
    s64 temp_v0;
    s64 var_v0;
    s64 var_v1;

    if (arg0 == 0) {
        func_002EA050((s32) D_0037C090);
        return -3;
    }
    var_v1 = *(s64 *) (arg0 + 0x10);
    if (var_v1 > 0x7FFFF7FFLL) {
        func_002F32C0(*(s32 *) (arg0 + 4));
        var_v0 = -5;
        if (func_002F1ED0(*(s32 *) (arg0 + 4)) != 4) {
            temp_v0 = func_002F2CA0(*(s32 *) (arg0 + 4));
            *(s64 *) (arg0 + 0x10) = temp_v0;
            var_v1 = temp_v0;
            var_v0 = (s64) (s32) var_v1;
        }
        return var_v0;
    }
    return (s64) (s32) var_v1;
}
