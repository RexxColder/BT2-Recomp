#include "common.h"

s32 func_002DE188(s32 arg0, s32 arg1);
void func_002DE1E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002C0670(s32 arg0, s32 arg1);
void func_002C8518(s32 arg0, s32 arg1, s32 arg2);
void func_002C8638(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002C8670(s32 arg0, s32 arg1);
s32 func_002C2FF0(s32 arg0, s32 arg1);

s32 func_002C83E8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    u8 *s2;
    u8 *s3;
    s32 temp;
    s32 v1;
    s32 v0;

    s2 = arg0 + 0x90C;
    s3 = *(u8 **)(arg0 + 0x1FC0);
    if (*(s32 *)(s2 + 0x10) != 0) {
        return 0;
    }

    if (func_002DE188(arg1, (s32)sp) != 0) {
        return func_002C2FF0((s32)arg0, 0xFF000F16);
    }
    func_002DE1E8(arg1, (s32)&sp[1], (s32)&sp[2], (s32)&sp[3]);

    if (func_002D07B0((s32)arg0, 0x3C) == 0) {
        *(s32 *)(s3 + 0x114) = 0;
    } else {
        temp = func_002C0670((s32)arg0, 1);
        v1 = sp[3];
        v0 = v1 < temp;
        if (v1 == -1) {
            v1 = sp[1];
            sp[3] = v1;
            v0 = v1 < temp;
        }
        *(s32 *)(s3 + 0x114) = (v0 == 0) ? temp : v1;
    }

    func_002C8518((s32)arg0, sp[0], arg3);
    func_002C8638((s32)s2, sp[0], arg2, sp[1]);
    return func_002C8670((s32)arg0, (s32)s2);
}
