#include "common.h"

extern void func_00148000();
extern s32 func_0014E258(s32 a0, u8 *a1);
extern void func_0014E1E0(s32 a0, u8 *a1, s32 a2, s32 a3);
extern s32 BtlScene_GetPackEntry(s32 a0, s32 a1);
extern s32 BtlTask_CreateChildList(u8 *a0, s32 a1, s32 a2);

s32 func_00162270(u8 *task, u8 *scene) {
    u8 *data;
    s32 n;

    data = *(u8 **)(task + 0x38);
    func_00148000(0x1E88);
    __builtin_memset(data, 0, 0x1E88);
    n = func_0014E258((s32)scene, data);
    func_0014E1E0((s32)scene, data + 0x1E80, 1, n);
    *(s32 *)(data + 0x1E84) = BtlScene_GetPackEntry(*(s32 *)(scene + 0x1C), 2);
    return BtlTask_CreateChildList(task, 2, 0xB20);
}
