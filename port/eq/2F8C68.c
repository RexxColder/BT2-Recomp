#include "common.h"

void func_002E9400(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_00354F38[] __attribute__((section(".data")));

void *func_002F8C68(void) {
    s32 s1;
    u8 *v1;
    u8 *s0;

    s1 = 0;
    v1 = D_00354F38;
    if (*(s32 *)D_00354F38 != 0) {
        s1 = 1;
        while (s1 < 0x10) {
            v1 += 0x3C;
            if (*(s32 *)v1 == 0) {
                break;
            }
            s1 += 1;
        }
    }
    if (s1 == 0x10) {
        return NULL;
    }
    s0 = D_00354F38 + s1 * 0x3C;
    memset(s0, 0, 0x3C);
    *(s32 *)s0 = 1;
    *(s32 *)(s0 + 4) = s1;
    *(s32 *)(s0 + 8) = 0;
    *(s32 *)(s0 + 0xC) = 0;
    func_002E9400(0x1F4, 0xAC44, (s32)(s0 + 0x30), (s32)(s0 + 0x32));
    memset(s0 + 0x28, 0, 8);
    return s0;
}
