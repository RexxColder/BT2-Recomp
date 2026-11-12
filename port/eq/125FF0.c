#include "common.h"

extern u8 *D_003876FC;

/* 0x00125FF0: record arg0 of the table at D_003876FC: NULL if the table pointer is NULL, arg0 < 0 or
 * arg0 >= table->count (+4); otherwise table->base (+0) + arg0 * 0x11F0. */
u8 *func_00125FF0(s32 arg0) {
    if (D_003876FC == NULL) {
        return NULL;
    }
    if (arg0 < 0) {
        return NULL;
    }
    if (arg0 >= *(s32 *)(D_003876FC + 0x4)) {
        return NULL;
    }
    return *(u8 **)D_003876FC + arg0 * 0x11F0;
}
