#include "common.h"

/* GUESS arity: a0..a2 are not written before this call, passed through */
s32 BtlCharApi_GetOpponentObjId(s32 arg0, s32 arg1, s32 arg2);
void func_002DA928(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002DC680(s32 arg0, s32 arg1);
void func_002DCE00(s32 arg0);

void func_002C18F0(s32 arg0, s32 arg1, s32 *arg2) {
    s32 sp[4];
    s32 sp10;
    s32 sp14;
    s32 temp_v0;

    temp_v0 = BtlCharApi_GetOpponentObjId(arg0, arg1, (s32)arg2);
    if (temp_v0 != 0) {
        func_002DA928(temp_v0, arg0, arg1, (s32)&sp10, (s32)&sp14);
        if (sp14 & 0x10000) {
            func_002DC680(temp_v0, (s32)sp);
            func_002DCE00(temp_v0);
            *arg2 = sp[3];
        }
    }
}
