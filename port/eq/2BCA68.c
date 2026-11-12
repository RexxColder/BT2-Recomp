#include "common.h"

void Rand_Range(void *arg0);
void func_002B74A0(u8 *arg0);
s32 func_002CED10(s32 arg0);
s32 func_002D0468(s32 arg0);
s32 func_003001B8(s32 arg0);
extern u8 D_00379F40[] __attribute__((section(".data")));

/* 0x002BCA68(obj): s1 = obj->+0x3C; when byte +0x71 is 1 and func_003001B8(obj->+0x48) is 0: if func_002CED10(s1) is
 * nonzero, Rand_Range(&D_00379F40); byte +0x71 = 0. When half +0x70 is 0 and func_003001B8(obj->+0x48) is 0:
 * func_002B74A0(obj). Finally, when func_002D0468(s1) == 6: word +4 = 3. */
void func_002BCA68(u8 *arg0) {
    s32 s1 = *(s32 *)(arg0 + 0x3C);

    if ((s8)arg0[0x71] == 1 && func_003001B8(*(s32 *)(arg0 + 0x48)) == 0) {
        if (func_002CED10(s1) != 0) {
            Rand_Range(D_00379F40);
        }
        arg0[0x71] = 0;
    }
    if (*(u16 *)(arg0 + 0x70) == 0 && func_003001B8(*(s32 *)(arg0 + 0x48)) == 0) {
        func_002B74A0(arg0);
    }
    if (func_002D0468(s1) == 6) {
        *(s32 *)(arg0 + 4) = 3;
    }
}
