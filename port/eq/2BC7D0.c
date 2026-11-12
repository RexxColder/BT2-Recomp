#include "common.h"

typedef s32 (*FnGet)(s32, s32);

s32 func_002D0468(s32 arg0);
s32 func_002BBC60(s32 arg0);
void func_002B6BD0(s32 arg0);
void func_002B7290(s32 arg0, s32 arg1);
s32 func_002C1120(s32 arg0);
void Rand_Range(s32 arg0);
void func_002BBD28(s32 arg0, s32 arg1);
extern u8 D_00379EE0[] __attribute__((section(".data")));

void func_002BC7D0(u8 *arg0) {
    u8 *p;
    u8 *p2;
    u8 *obj;
    s32 enter;

    if (func_002D0468(*(s32 *)(arg0 + 0x3C)) != 3) {
        return;
    }
    p = arg0 + 0x284;
    enter = 0;
    if (*(s32 *)p != 1) {
        enter = 1;
    } else if (func_002BBC60((s32)p) == 2) {
        enter = 1;
    } else {
        obj = *(u8 **)(p + 0x14);
        if (((FnGet)(*(s32 *)(*(u8 **)obj + 0x24)))((s32)obj, 1) == 0) {
            enter = 1;
        }
    }
    if (enter == 0) {
        return;
    }

    p2 = arg0 + 0x2A4;
    if (*(s32 *)p2 == 1 && func_002BBC60((s32)p2) != 2) {
        obj = *(u8 **)(p2 + 0x14);
        if (((FnGet)(*(s32 *)(*(u8 **)obj + 0x24)))((s32)obj, 1) != 0) {
            return;
        }
    }

    func_002B6BD0((s32)arg0);
    if (*(s8 *)(arg0 + 0x72) == 0) {
        func_002B7290((s32)arg0, 0);
    }
    if (*(s8 *)(arg0 + 0x70) == 1 && func_002C1120(*(s32 *)(arg0 + 0x3C)) != 0) {
        Rand_Range((s32)D_00379EE0);
    }
    if (*(s8 *)(arg0 + 0x72) != 0) {
        return;
    }
    func_002BBD28((s32)p, 0);
    func_002BBD28((s32)p2, 0);
}
