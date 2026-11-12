#include "common.h"

s32 func_002C3210(u8 *arg0);
void func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002CE6D8(u8 *arg0);
void func_002D05E8(u8 *arg0, s32 arg1, s32 arg2);
void func_002D2F30(u8 *arg0, s32 arg1);
extern void *memcpy(void *dst, const void *src, u32 n);

/* 0x002CFFD0: func_002C3210(obj) != 0 -> func_002C2FF0(0, 0xFF000158). Else s1 = obj+0x36B0; s1 == 0 -> return.
 * func_002CE6D8(obj) != 0 -> return; else func_002D05E8(obj, 0x2F, 0), func_002D05E8(obj, 5, 0) if s1+0xDB8 == 0,
 * func_002D05E8(obj, 6, 0) if s1+0xDBC == 0; copy 12 bytes arg1 to obj+0x36B4; tail func_002D2F30(obj, 0xD). */
void func_002CFFD0(u8 *arg0, u8 *arg1) {
    u8 *s1;

    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF000158);
        return;
    }
    s1 = (u8 *)*(s32 *)(arg0 + 0x36B0);
    if (s1 == 0) {
        return;
    }
    if (func_002CE6D8(arg0) != 0) {
        return;
    }
    func_002D05E8(arg0, 0x2F, 0);
    if (*(s32 *)(s1 + 0xDB8) == 0) {
        func_002D05E8(arg0, 5, 0);
    }
    if (*(s32 *)(s1 + 0xDBC) == 0) {
        func_002D05E8(arg0, 6, 0);
    }
    memcpy(arg0 + 0x36B4, arg1, 0xC);
    func_002D2F30(arg0, 0xD);
}
