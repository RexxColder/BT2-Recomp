#include "common.h"

s32 func_00106A00(s32 arg0, s32 arg1);

void func_00107ED8(s32 arg0, s32 arg1) {
    /* the callee result only feeds a harmless byte load (nothing is stored) */
    func_00106A00(arg0, arg1);
}
