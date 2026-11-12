#include "common.h"

typedef void (*FnV4)(s32, s32, s32, s32);
typedef void (*FnV3)(s32, s32, s32);

s32 func_002F8E20(s32 arg0);
void func_002E80B8(s32 arg0);
void func_002E8280(s32 arg0);
void func_002E93C0(void);
void func_002E93D8(void);
void func_002F8F30(s32 arg0);
void func_002F8F00(s32 arg0);
extern FnV4 D_00347BE4 __attribute__((section(".data")));

void func_002E8408(u8 *arg0) {
    s32 v;
    u8 *s1;
    s32 s2;
    s32 a2p;
    s32 a3v;

    v = *(s32 *)(arg0 + 4);
    if (v == 1) {
        if (func_002F8E20(*(s32 *)(arg0 + 8)) != 0) {
            v = *(s32 *)(arg0 + 4);
        } else {
            ((FnV4)(*(s32 *)(arg0 + 0x78)))(*(s32 *)(arg0 + 0x7C), (s32)(arg0 + 0x68),
                                            (s32)(arg0 + 0x6C), (s32)(arg0 + 0x70));
            func_002E80B8((s32)arg0);
            *(s32 *)(arg0 + 4) = 2;
            v = 2;
        }
    }
    if (v == 2) {
        func_002F8F30(*(s32 *)(arg0 + 8));
        if (func_002F8E20(*(s32 *)(arg0 + 8)) == 3) {
            if (*(s32 *)(arg0 + 0xE8) != 0) {
                s1 = *(u8 **)(arg0 + 8);
                func_002E93C0();
                if ((*(s32 *)(s1 + 0x10) << 5) > 0) {
                    s2 = 0;
                    do {
                        a2p = *(s32 *)(s1 + 0x20) + (s2 * 2);
                        a3v = *(s32 *)(s1 + 0x24) + (s2 * 2);
                        D_00347BE4((s32)arg0, *(s16 *)a2p, a2p, a3v);
                        s2 += 1;
                    } while (s2 < (*(s32 *)(s1 + 0x10) << 5));
                }
                func_002E93D8();
            }
            func_002E8280((s32)arg0);
            func_002F8F00(*(s32 *)(arg0 + 8));
            ((FnV3)(*(s32 *)(arg0 + 0x80)))(*(s32 *)(arg0 + 0x84), *(s32 *)(arg0 + 0x94),
                                            *(s32 *)(arg0 + 0x90));
            *(s32 *)(arg0 + 4) = 3;
        }
    }
}
