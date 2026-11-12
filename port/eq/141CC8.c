#include "common.h"

s32 func_00141CC8(s32 arg0) {
    if (arg0 == 0x75) {
        return 3;
    }
    if (arg0 < 0x76) {
        if (arg0 < 0x58) {
            if (arg0 < 0x55) {
                if (arg0 < 0x53) {
                    return 0;
                }
                return 2;
            }
            return 0;
        }
        if (arg0 < 0x61) {
            if (arg0 < 0x59) {
                return 3;
            }
            return 2;
        }
        if (arg0 != 0x71) {
            return 0;
        }
        return 2;
    }
    if (arg0 == 0x94) {
        return 3;
    }
    if (arg0 < 0x95) {
        if (arg0 == 0x90) {
            return 2;
        }
        return 0;
    }
    if (arg0 < 0x10E) {
        return 0;
    }
    if (arg0 < 0x112) {
        return 3;
    }
    if (arg0 < 0x154) {
        return 0;
    }
    if (arg0 < 0x156) {
        return 3;
    }
    return 0;
}
