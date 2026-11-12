#include "common.h"

void func_00284E68(s32 arg0, s32 arg1, f32 farg0);
void func_002A86E8(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern void func_00103CB0(void);

s32 func_001040E0(s32 arg0) {
    s32 sp[8] = {0}; /* func_002A86E8 copies 0x18 bytes from this block; asm leaves the tail unwritten */
    s32 var_v0;

    var_v0 = 0;
    if ((arg0 >= 0) && (*(s32 *)(D_003876A0 + 0xD4) != arg0)) {
        func_00284E68(2, 1, 1.0f);
        *(s32 *)(D_003876A0 + 0xD4) = arg0;
        sp[0] = 0;
        sp[1] = arg0;
        func_002A86E8((s32)sp, (s32)func_00103CB0, 0);
        var_v0 = 1;
    }
    return var_v0;
}
