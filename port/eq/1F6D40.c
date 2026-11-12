#include "common.h"

void *memset(void *s, s32 c, u32 n);
s32 func_00211270(void);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

void BtlChars_UpdateFreeze(void) {
    s32 arr[4];
    s32 i;
    s32 maxv;
    u8 *obj;

    memset(arr, 0, 8);
    maxv = 0;
    for (i = 0; i < func_00211270(); i++) {
        obj = (u8 *)func_00211288(i);
        if (func_00211310((s32)obj, 9, 0x10000)) {
            arr[i] = 2;
        } else if (func_00211310((s32)obj, 9, 0x20000)) {
            arr[i] = 1;
        }
        if (arr[i] > maxv) {
            maxv = arr[i];
        }
    }

    if (maxv > 0) {
        for (i = 0; i < func_00211270(); i++) {
            obj = (u8 *)func_00211288(i);
            *(s32 *)(obj + 0x98C) = 0;
            *(s32 *)(obj + 0x988) = 1;
        }

        for (i = 0; i < func_00211270(); i++) {
            obj = (u8 *)func_00211288(i);
            if (arr[i] == maxv) {
                *(s32 *)(obj + 0x988) = 0;
                *(s32 *)(obj + 0x98C) = 0;
                if (maxv >= 2) {
                    break;
                }
            }
            if (func_00211310((s32)obj, 9, 0x40000) && maxv == 1) {
                *(s32 *)(obj + 0x98C) = 0;
                *(s32 *)(obj + 0x988) = 0;
            }
        }
    }

    for (i = 0; i < func_00211270(); i++) {
        obj = (u8 *)func_00211288(i);
        if (*(s32 *)(obj + 0x984) > 0) {
            s32 v = *(s32 *)(obj + 0x984) - 1;
            if (v < 0) {
                v = 0;
            }
            *(s32 *)(obj + 0x984) = v;
        }
        if (*(s32 *)(obj + 0x988) != 0) {
            if (*(s32 *)(obj + 0x98C) != 0) {
                *(s32 *)(obj + 0x98C) = *(s32 *)(obj + 0x98C) - 1;
            } else {
                *(s32 *)(obj + 0x984) = *(s32 *)(obj + 0x988);
                *(s32 *)(obj + 0x988) = 0;
            }
        }
    }
}
