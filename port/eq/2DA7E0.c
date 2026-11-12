#include "common.h"

s32 func_002DCC38(void *arg0);
void func_002DCA68(s32 arg0, s32 arg1);

void func_002DA7E0(void *arg0, s32 arg1) {
    if (func_002DCC38(arg0) != 0) {
        func_002DCA68(0, 0xFF020302);
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x10) = arg1;
}
