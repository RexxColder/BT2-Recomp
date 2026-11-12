#include "m2c_macros.h"

s32 Gsc_GetFileHandle(s32 arg0) {
    return arg0 & 0xFFFF0000;
}
