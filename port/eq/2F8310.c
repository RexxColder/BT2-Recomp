#include "common.h"

s32 func_002F0388(s32 arg0);
s32 func_002F1328(s32 arg0);
void func_002F1480(s32 arg0, s32 arg1);
s32 func_002F14E0(s32 arg0);
extern s32 D_00354F20 __attribute__((section(".data")));
extern s32 D_00354F24 __attribute__((section(".data")));

/* 0x002F8310: if the byte at +0x6C is 0, +0xC4 is non-zero and func_002F1328(word +4) >= word +0xC4, then
 * func_002F1480(word +4, -1). If func_002F0388(word +4) == 3: count = func_002F14E0(word +4) (stored in D_00354F20);
 * for each of the first count 4-byte object slots at +0x18, r = vtable[+0x24](obj, 1) (stored in D_00354F24) until
 * r >= 0x40; when all count slots were below 0x40, byte +1 = 4. */
void func_002F8310(u8 *arg0) {
    s32 count;
    s32 i;
    u8 *slot;

    if (*(s8 *)(arg0 + 0x6C) == 0 && *(s32 *)(arg0 + 0xC4) != 0 &&
        func_002F1328(*(s32 *)(arg0 + 4)) >= *(s32 *)(arg0 + 0xC4)) {
        func_002F1480(*(s32 *)(arg0 + 4), -1);
    }
    if (func_002F0388(*(s32 *)(arg0 + 4)) == 3) {
        i = 0;
        slot = arg0 + 0x18;
        count = func_002F14E0(*(s32 *)(arg0 + 4));
        D_00354F20 = count;
        while (i < count) {
            u8 *obj = *(u8 **)slot;
            s32 r;

            slot += 4;
            r = (*(s32 (**)(u8 *, s32))(*(u8 **)obj + 0x24))(obj, 1);
            D_00354F24 = r;
            if (r >= 0x40) {
                break;
            }
            i += 1;
        }
        if (i == count) {
            arg0[1] = 4;
        }
    }
}
