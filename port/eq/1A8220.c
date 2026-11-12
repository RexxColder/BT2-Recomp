#include "common.h"

s32 BtlTask_SetDead(s32 arg0, s32 arg1);
void func_001A8D20(s32 arg0, s32 arg1);

void func_001A8220(u8 *arg0) {
    u8 *t = *(u8 **)(arg0 + 0x38);
    s32 flag = *(s32 *)(t + 0x28) & 1;

    *(s32 *)(t + 0x24) += 1;
    if (flag != 0) {
        BtlTask_SetDead((s32)arg0, flag);
        return;
    }
    func_001A8D20((s32)arg0, flag);
}
