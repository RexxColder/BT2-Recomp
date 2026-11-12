#include "common.h"

void func_001CDBD8(u8 *arg0, u8 *arg1, u8 *arg2);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_003878C8;

void func_001CCE30(void) {
    u8 *s0;

    if (D_003878C8 == NULL) {
        return;
    }
    s0 = *(u8 **)(D_003878C8 + 0x210);
    if (s0 == NULL) {
        return;
    }
    *(s32 *)(s0 + 0x00) = 0;
    do {
        *(s32 *)(s0 + 0x08) = 0;
        func_001CDBD8(D_003878C8 + 0x210, D_003878C8 + 0x214, s0);
        s0 = *(u8 **)(s0 + 0x0C);
        if (s0 == NULL) {
            break;
        }
        *(s32 *)(s0 + 0x00) = 0;
    } while (1);
    memset(D_003878C8 + 0x218, 0, 0x3C);
    memset(D_003878C8 + 0x120, 0, 0xF0);
}
