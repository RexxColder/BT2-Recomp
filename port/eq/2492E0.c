#include "common.h"

/* 0x002492E0: when arg3 != 0, a switch on arg0 - 0x38 (cases 0..2 -> 14, 9/10/12 -> 0, 21 -> 63) returns directly.
 * Otherwise scan arg1 records of 0x2C bytes (word 1 = count, words 2.. = ids): return the index of the first record
 * whose word 0 (count == 0) or one of its first ids equals arg0; -1 if none. */
s32 func_002492E0(s32 arg0, s32 arg1, s32 *arg2, s32 arg3) {
    s32 *rec;
    s32 i;
    s32 k;
    s32 cnt;
    u32 idx;

    if (arg3 != 0) {
        idx = arg0 - 0x38;
        if (idx < 0x16) {
            switch (idx) {
            case 0:
            case 1:
            case 2:
                return 0x0E;
            case 9:
            case 10:
            case 12:
                return 0;
            case 21:
                return 0x3F;
            default:
                break;
            }
        }
    }
    for (i = 0, rec = arg2; i < arg1; i++, rec += 11) {
        cnt = rec[1];
        if (cnt == 0) {
            if (rec[0] == arg0) {
                return i;
            }
        } else if (cnt > 0) {
            if (rec[2] == arg0) {
                return i;
            }
            for (k = 1; k < cnt; k++) {
                if (rec[k + 2] == arg0) {
                    return i;
                }
            }
        }
    }
    return -1;
}
