#include "common.h"

void *func_002E03F8(void);
void func_002E0590(void *arg0, s32 arg1);
void *func_002E0448(void *arg0);
s32 func_002E07D8(void *arg0);

void *func_002E03A0(void) {
    void *temp_v0;
    void *var_v0;

    var_v0 = func_002E03F8();
    if (var_v0 != NULL) {
        func_002E0590(var_v0, 0x40C);
        temp_v0 = func_002E0448(var_v0);
        *(s32 *)((u8 *)temp_v0 + 0x3B4) = func_002E07D8(temp_v0);
        var_v0 = temp_v0;
    }
    return var_v0;
}
