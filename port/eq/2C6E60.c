#include "common.h"

s32 func_002C6EB0(s32 arg0);
void func_002C7088(s32 arg0, s32 arg1);

s32 func_002C6E60(s32 arg0, s32 arg1) {
    s32 v = func_002C6EB0(arg0);

    if (v != -1) {
        func_002C7088(arg0, arg1);
        return 0;
    }
    return v;
}
