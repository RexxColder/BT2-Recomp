#include "common.h"

s32 func_002EFE80(s32 arg0);
s32 func_002F4590(s32 arg0);
void func_002F5CE8(void);
s32 func_002F6F00(s32 arg0);
void func_002F7300(s32 arg0, s32 arg1);

void func_002F7680(s32 arg0, s32 arg1) {
    s32 temp_v0;

    func_002F7300(arg0, arg1);
    temp_v0 = func_002F6F00(arg0);
    if (temp_v0 != 0) {
        for (;;) {
            if (func_002EFE80(temp_v0) == 2) {
                break;
            }
            func_002F5CE8();
            if (func_002F4590(arg0) == 5) {
                break;
            }
        }
    }
}
