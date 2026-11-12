#include "common.h"

void func_001C9388(u8 *arg0, u8 *arg1, u8 *arg2);
extern u8 *D_003878B4;

s32 func_001C92E8(s32 arg0, s32 arg1) {
    u8 *node = *(u8 **)(D_003878B4 + 0x120);

    while (node != NULL) {
        if (*(s32 *)(node + 4) == arg1 && *(s32 *)node == arg0) {
            *(s32 *)node = 0;
            *(s32 *)(node + 8) = 0;
            func_001C9388(D_003878B4 + 0x120, D_003878B4 + 0x124, node);
            return 1;
        }
        node = *(u8 **)(node + 0xC);
    }
    return 0;
}
