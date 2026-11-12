#include "common.h"

/* Looks up a node by key: func_00106A00(table, key, a2) (0x106A00; NULL when not found). The wrappers forward their
 * own a0/a1/a2 untouched. */
extern void *func_00106A00(s32 arg0, s32 arg1, s32 arg2);

/* Returns the byte at +0x1D of the current object, or 0 when there is none. */
s32 BtlCur_GetByte1D(s32 a0, s32 a1, s32 a2) {
    void *obj;

    obj = func_00106A00(a0, a1, a2);
    if (obj != NULL) {
        return (u8)(*(u8 *)((u8 *)obj + 0x1D));
    }
    return (u8)(0);
}
