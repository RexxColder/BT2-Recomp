#include "common.h"

/* Looks up a node by key: func_00106A00(table, key, a2) (0x106A00; NULL when not found). The wrappers forward their
 * own a0/a1/a2 untouched. */
extern void *func_00106A00(s32 arg0, s32 arg1, s32 arg2);

/* Stores the low byte of value at +0x19 of the current object, if there is one. */
void BtlCur_SetByte19(s32 a0, s32 a1, s32 value) {
    void *obj;
    u8 val8;

    val8 = (u8)(value & 0xFF);
    obj = func_00106A00(a0, a1, value);
    if (obj != NULL) {
        *(s8 *)((u8 *)obj + 0x19) = (s8)val8;
    }
}
