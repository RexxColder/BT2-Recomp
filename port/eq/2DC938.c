#include "common.h"

void func_002DA708(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002DCA40(s32 arg0);
extern u8 *D_00347600 __attribute__((section(".data")));

s32 func_002DC938(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 *p;
    s32 n;

    D_00347600 = arg1;
    func_002DA708((s32)arg1, 0, (arg0 << 6) + 4, arg3);
    func_002DCA40((s32)D_00347600);
    *(s32 *)(D_00347600 + 0xC) = arg0;
    p = D_00347600 + 0x10;
    if (arg0 > 0) {
        n = arg0;
        do {
            n -= 1;
            *(s32 *)p = 1;
            p += 0x100;
        } while (n != 0);
    }
    return 0;
}
