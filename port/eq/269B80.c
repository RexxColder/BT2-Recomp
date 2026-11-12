#include "common.h"

s32 func_00269A40(s32 arg0, s32 arg1);

/* 0x00269B80: maps a node code (0..17) to a lookup key of func_00269A40 (table jtbl_003767C0); any other code
 * gives 0. */
s32 BtlObj_GetNodeByCode(s32 arg0, s32 arg1) {
    static const s32 keys[18] = { 0x03, 0x07, 0x0A, 0x0B, 0x0E, 0x0F, 0x13, 0x14, 0x15,
                                  0x21, 0x22, 0x23, 0x2E, 0x40, 0x41, 0x00, 0x1F, 0x2D };

    if ((u32)arg1 >= 0x12) {
        return 0;
    }
    return func_00269A40(arg0, keys[arg1]);
}
