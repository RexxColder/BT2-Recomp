#include "common.h"

u8 *func_0028BAA8(s32 arg0);
void func_002974F8(s32 arg0, s32 arg1);
void sceSifInitRpc(s32 arg0);
void sceSifBindRpc(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_003B0E00[] __attribute__((section(".data")));
extern u8 *gSndRpc;

void func_00297580(s32 arg0, s32 arg1) {
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = func_0028BAA8(0x168);
    gSndRpc = temp_v0;
    memset(temp_v0, 0, 0x168);
    sceSifInitRpc(0);
    temp_v1 = gSndRpc;
    for (;;) {
        sceSifBindRpc((s32)(temp_v1 + 0x40), 0x02000004, 0);
        temp_v1 = gSndRpc;
        if (*(s32 *)(temp_v1 + 0x64) != 0) {
            break;
        }
        var_v0 = 0x270B;
        while (var_v0 != -1) {
            var_v0 -= 4;
        }
    }
    *(s32 *)(D_003B0E00 + 4) = arg0;
    *(s32 *)(D_003B0E00 + 8) = arg1;
    func_002974F8(0x10, (s32)D_003B0E00);
}
