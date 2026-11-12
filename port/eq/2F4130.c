#include "common.h"

void func_002F0390(s32 arg0, s32 arg1);
void func_002F0450(s32 arg0);
void func_002F5F80(s32 arg0, s32 arg1, s32 arg2);
void func_00307F00(s32 arg0);
extern s32 D_0034AED8 __attribute__((section(".data")));

void func_002F4130(s32 arg0, s32 arg1) {
    u8 *p;
    s32 s2;
    s32 *slot;
    s32 obj;
    s32 temp;

    p = (u8 *)arg0;
    s2 = 0;
    if (*(s8 *)(p + 3) > 0) {
        slot = (s32 *)(p + 0x18);
        obj = *slot;
        for (;;) {
            slot += 1;
            s2 += 1;
            ((void (*)(s32))(*(s32 *)(*(s32 *)obj + 0x14)))(obj);
            if (!(s2 < *(s8 *)(p + 3))) {
                break;
            }
            obj = *slot;
        }
    }
    func_002F0390(*(s32 *)(p + 4), arg1);
    *(s32 *)(p + 0x14) = arg1;
    func_002F0450(*(s32 *)(p + 4));
    *(s8 *)(p + 1) = 1;
    *(s32 *)(p + 0x8C) = 0x7FFFFFFF;
    *(s32 *)(p + 0x90) = -1;
    *(s32 *)(p + 0x4C) = 0;
    *(s8 *)(p + 0x71) = 0;
    *(s32 *)(p + 0x9C) = 0;
    *(s32 *)(p + 0xA4) = 0;
    *(s32 *)(p + 0xC4) = 0;
    *(s32 *)(p + 0xA0) = D_0034AED8;
    if (*(s8 *)(p + 2) == 4) {
        func_002F5F80(arg0, 0, 4);
    }
    temp = *(s32 *)(p + 0x74);
    if (temp != 0) {
        func_00307F00(temp);
    }
}
