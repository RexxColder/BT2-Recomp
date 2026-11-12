#include "m2c_macros.h"

s32 func_0023E520();                                /* extern */

s32 func_0023F2D8(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    s32 temp_v0;
    s32 var_a0;

    temp_v0 = func_0023E520(r_a0);
    var_a0 = 5;
    switch (temp_v0) {
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2C:
    case 0x2D:
    case 0x3E:
    case 0x41:
    case 0x5C:
        var_a0 = 6;
        break;
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x3F:
    case 0x42:
    case 0x48:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
        var_a0 = 7;
        break;
    }
    return var_a0;
}
