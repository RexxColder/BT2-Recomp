#include "common.h"

s32 func_002DCE50(s32 arg0);
s32 func_002DCFE8(s32 arg0, s32 arg1, s32 arg2);
void *memcpy(void *arg0, void *arg1, u32 arg2);

s32 func_002C67D0(u8 *arg0, s32 arg1, s32 *arg2) {
    u8 sp[8];
    s32 ptrA;
    s32 lenA;
    s32 ptrB;
    s32 lenB;
    s32 a3;
    s32 s0;
    s32 s1;
    s32 s3;
    s32 s4;
    s32 v;

    *arg2 = 0;
    ptrA = *(s32 *)(arg0 + 0);
    lenA = *(s32 *)(arg0 + 4);
    s1 = func_002DCFE8(ptrA, lenA, arg1);
    if (s1 != 0) {
        *arg2 = func_002DCE50(s1);
        return s1;
    }
    a3 = *(s32 *)(arg0 + 0xC);
    if (a3 == 0) {
        return s1;
    }
    s3 = (lenA < 4) ? lenA : 3;
    s0 = (a3 < 4) ? a3 : 3;
    memcpy(sp, (void *)(ptrA + lenA - s3), s3);
    ptrB = *(s32 *)(arg0 + 8);
    memcpy(sp + s3, (void *)ptrB, s0);
    s0 = s3 + s0 - 3;
    s4 = 0;
    while (s4 < s0) {
        v = func_002DCE50((s32)(sp + s4));
        if ((v & arg1) != 0) {
            *arg2 = v;
            return ptrA + lenA - s3 + s4;
        }
        s4 += 1;
    }
    ptrB = *(s32 *)(arg0 + 8);
    lenB = *(s32 *)(arg0 + 0xC);
    s1 = func_002DCFE8(ptrB, lenB, arg1);
    if (s1 == 0) {
        return 0;
    }
    *arg2 = func_002DCE50(s1);
    return s1;
}
