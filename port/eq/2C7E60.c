#include "common.h"

u64 func_002E0BB8(s64 arg0, s64 arg1, s64 arg2);
extern s32 D_0037A530[];
extern s32 D_0037A2D8[];
extern s32 D_0037A300[];
extern s32 D_0037A320[];

s32 func_002C7E60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    s32 perUnit;
    s32 unitsPerSec;
    s32 v10;
    s32 v12;
    s32 v13;
    s32 v14;
    s32 *tbl;
    s32 v16;
    s32 v19;
    s32 v20;
    s32 v21;
    s32 v22;
    s32 v24;
    s32 v25;
    s32 v26;
    s32 v28;
    s32 v29;
    s32 v33;
    s32 result;

    perUnit = D_0037A530[arg1];
    unitsPerSec = D_0037A2D8[arg1];
    v10 = (s32)func_002E0BB8(arg0, 2 * perUnit, 90000000);
    *(s32 *)(arg4 + 0x00) = arg1;
    v12 = (v10 >> 1) - arg3;
    *(s32 *)(arg4 + 0x04) = arg2;
    *(s16 *)(arg4 + 0x1E) = v10 & 1;
    if (v12 < 0) {
        v12 = 0;
    }

    if (arg2 != 0 && (perUnit == 29970 || perUnit == 59940)) {
        tbl = (perUnit == 29970) ? D_0037A300 : D_0037A320;

        v16 = v12 % tbl[0];
        v21 = v12 / tbl[0];
        v19 = v16 / tbl[1];
        v20 = v16 % tbl[1];
        v22 = v19;
        if (v20 < tbl[2]) {
            v24 = 0;
            v25 = v20 / tbl[5];
            v26 = v20 % tbl[5];
        } else {
            v28 = (v20 - tbl[2]) / tbl[3];
            v29 = (v20 - tbl[2]) % tbl[3];
            v24 = v28 + 1;
            if (v29 < tbl[4]) {
                v25 = 0;
                v26 = v29 + tbl[7];
            } else {
                v25 = (v29 - tbl[4]) / tbl[5] + 1;
                v26 = (v29 - tbl[4]) % tbl[5];
            }
        }
        result = tbl[6];
        v33 = result * v22 + v24;
    } else {
        v13 = v12 / unitsPerSec;
        v14 = v12 % unitsPerSec;
        v26 = v14;
        v25 = v13 % 60;
        v21 = v13 / 60 / 60;
        v33 = v13 / 60 % 60;
        result = v21;
    }

    *(s32 *)(arg4 + 0x14) = v26;
    *(s32 *)(arg4 + 0x08) = v21;
    *(s32 *)(arg4 + 0x0C) = v33;
    *(s32 *)(arg4 + 0x10) = v25;
    return result;
}
