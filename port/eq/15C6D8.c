#include "common.h"

extern void func_00148000();
s32 func_0014E258(u8 *arg0, u8 *b);
extern void BtlScene_FillPackEntries();
extern s32 BtlTask_CreateChildList();

s32 func_0015C6D8(u8 *task, s32 arg1) {
    u8 *obj = *(u8 **)(task + 0x38);

    func_00148000(0x1E88);
    __builtin_memset(obj, 0, 0x1E88);
    BtlScene_FillPackEntries(arg1, obj + 0x1E80, 1, func_0014E258((u8 *)arg1, obj));
    return BtlTask_CreateChildList(task, 2, 0xAC0);
}
