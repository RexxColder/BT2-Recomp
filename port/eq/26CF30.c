#include "common.h"

s32 func_0026CA80(s32 arg0, s32 arg1);

s32 func_0026CF30(s32 arg0, s32 arg1) {
    u8 *p;

    p = (u8 *)func_0026CA80(arg0, arg1);
    return (u8)p[4] | ((u8)p[5] << 8);
}
