#include "common.h"

/* 0x002C6A90 (a0 = obj, a1 = mode value, a2 = flags, a3 = gate, t0 = out flag pointer).
   obj+0x1FC0 = rec (record pointer), obj+0x1FC8 = s2 value, obj+0x978 = state word. */

s32 func_002CC9B8(s32 arg0);
s32 func_002C71D8(s32 arg0);
s32 func_002CABE8(s32 arg0);
s32 func_002C6748(s32 arg0);
s32 func_002C0750(s32 arg0, s32 arg1, s32 *arg2);
void func_002CAC08(s32 arg0, s32 arg1);
void func_002C6DA8(s32 arg0);
s32 func_002C1180(s32 arg0);
s32 func_002C6E60(s32 arg0, s32 arg1);
s32 func_002C11E8(s32 arg0);
void func_002C7088(s32 arg0, s32 arg1);
s32 func_002C7190(s32 arg0, s32 arg1, s32 arg2);
void func_002C6D58(s32 arg0, void *arg1);
s32 func_002C7288(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 *arg4);
s32 func_002C8828(s32 arg0, void *arg1);
s32 func_002C8D98(s32 arg0, s32 arg1);
s32 func_002C8F00(s32 arg0, s32 arg1);
s32 func_002C9A50(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C6A90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4) {
    u8 *obj = (u8 *)arg0;
    u8 *rec;
    u8 v19[16];
    s32 v20;
    s32 v21[3];
    s32 flags = arg2;
    s32 res;

    *arg4 = 0;
    rec = (u8 *)*(s32 *)(obj + 0x1FC0);
    *(s32 *)(obj + 0x978) = 0;

    if (func_002CC9B8(arg0) == 0) {
        if (func_002C71D8(arg0) == 1) {
            func_002CABE8(arg0);
            return 0;
        }
        *(s32 *)(obj + 0x978) = 1;
        return func_002C6748(arg0);
    }

    if (*(s32 *)(rec + 0x78) != 0xCC) {
        flags &= 0xCC;
    } else if (*(s32 *)(rec + 0x170) == 0) {
        flags &= 0xCC;
    }

    res = func_002C0750(arg0, *(s32 *)(obj + 0x1FC8), &v20);
    if (res != 0) {
        return 0;
    }
    if (v20 == 0) {
        return 0;
    }

    if ((flags & 0xC8) != 0) {
        func_002CAC08(arg0, 1);
    }

    if (flags == 0x80) {
        func_002C6DA8(arg0);
        if (func_002C1180(arg0) != 0) {
            if (func_002C6E60(arg0, v20) != 0) {
                return 0;
            }
            *arg4 = 1;
            return 0;
        }
        if (func_002C11E8(arg0) != 0) {
            func_002C7088(arg0, v20);
            *arg4 = 1;
            return 0;
        }
    }

    if (arg3 == 0) {
        if (func_002C7190(arg0, arg1, flags) != 0) {
            func_002CABE8(arg0);
            return 0;
        }
        if (arg1 < 5) {
            *(s32 *)(obj + 0x978) = 1;
            return 0;
        }
    }

    if ((flags & 0x4C) != 0) {
        func_002C6D58(arg0, v19);
        res = func_002C7288(arg0, v19, v20, flags, v21);
        if (res != 0) {
            return res;
        }
        if (v21[0] == 0) {
            if ((flags & *(s32 *)(rec + 0x78)) != 0) {
                *(s32 *)(rec + 0x78) = 204;
            }
            *(s32 *)(rec + 0x170) = 1;
        }
        if (flags == 0x40 && v21[0] == -2) {
            *(s32 *)(rec + 0x78) = 0xC0;
        }
        *arg4 = 1;
        return 0;
    }

    if ((flags & 2) != 0) {
        func_002C6D58(arg0, v19);
        if (func_002C8828(arg0, v19) != 0) {
            res = func_002C8D98(arg0, v20);
            if (res != 0) {
                return res;
            }
            *arg4 = 1;
            return 0;
        }
        return func_002C8F00(arg0, v20);
    }

    if (flags != 0x80) {
        if (func_002C9A50(arg0, v20, 0xCC) > 0) {
            *arg4 = 1;
        }
    }
    return 0;
}
