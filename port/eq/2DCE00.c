#include "common.h"

void func_002DCA68(s32 arg0, s32 arg1);
s32 func_002DCC38(s32 arg0);

void func_002DCE00(s32 arg0) {
    if (func_002DCC38(arg0) != 0) {
        func_002DCA68(0, 0xFF020103);
        return;
    }
    *(s32 *)arg0 = 1;
}
