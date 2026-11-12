#include "common.h"

s32 func_0024AC08(s32 arg0) {
    s32 v1;

    v1 = arg0;
    if (arg0 < 0) {
        v1 = -v1;
    }
    if (v1 < 10) {
        return 1;
    }
    if (v1 < 100) {
        return 2;
    }
    if (v1 < 1000) {
        return 3;
    }
    if (v1 < 10000) {
        return 4;
    }
    if (v1 <= 0x1869F) {
        return 5;
    }
    if (v1 <= 0xF423F) {
        return 6;
    }
    if (v1 <= 0x98967F) {
        return 7;
    }
    if (v1 <= 0x5F5E0FF) {
        return 8;
    }
    return 1;
}
