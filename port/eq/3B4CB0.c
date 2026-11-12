#include "m2c_macros.h"

void func_2B4FD0(s32, void *);
s32 func_003B5350(void *, s32, s32);
void func_2B58F0(s32);
s32 func_2B8328(s32);
void func_003B5620(s32, s32, s32, void *);

s32 func_003B4CB0(void *arg0, void *arg1) {
    s32 ret;
    s32 r;

    ret = 0;
    if (arg0 != 0) {
        func_2B4FD0(M2C_FIELD(arg0, s32 *, 0xC0), arg0);
        if (M2C_FIELD(arg0, s32 *, 0) != 0) {
            r = func_003B5350(M2C_FIELD(arg0, void **, 0), M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, s32 *, 0x10));
            M2C_FIELD(arg0, s32 *, 0xD0) = r;
            func_2B58F0(M2C_FIELD(arg0, s32 *, 0xC0));
        }
        r = func_2B8328(M2C_FIELD(arg0, s32 *, 0xC0));
        if (r == 0 || r == 2 || r == 3) {
            func_003B5620(M2C_FIELD(arg0, s32 *, 0xD0), M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, s32 *, 0x10), arg1);
            ret = 1;
        }
    }
    return ret;
}
