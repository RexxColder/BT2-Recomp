#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002CA830(s32 arg0, s32 arg1, s32 arg2);
s32 func_002CAB18(s32 arg0, s32 arg1);
s32 func_002CAB60(s32 arg0, s32 arg1);
s32 func_002CABA0(s32 arg0, s32 arg1);
void func_002CAD80(s32 arg0);

s32 func_002CA708(u8 *arg0, s32 arg1, s32 arg2) {
    s32 s1;
    s32 *s2;
    s32 s3;

    s3 = *(s32 *)(arg0 + 0x1FC0);
    if (*(s32 *)(arg0 + 0x58) == 2) {
        s1 = func_002CAB60((s32)arg0, arg2);
        if (s1 == 0) {
            return func_002C2FF0((s32)arg0, 0xFF000F1F);
        }
        s2 = (s32 *)func_002CABA0((s32)arg0, s1);
        *s2 = 0;
        func_002CAD80(s1);
        return 0;
    }
    s2 = (s32 *)func_002CA830((s32)arg0, arg1, arg2);
    if (*s2 != 1) {
        return func_002C2FF0((s32)arg0, 0xFF000F0E);
    }
    s1 = func_002CAB18((s32)arg0, arg1);
    if (*(s32 *)(s3 + 0x70) != s1) {
        return func_002C2FF0((s32)arg0, 0xFF000F0F);
    }
    *s2 = 0;
    func_002CAD80(s1);
    return 0;
}
