#include "common.h"

extern u8 *D_00387A40;
extern s32 func_002623D8(void);
extern void func_0025E0B8(s32 a0, u8 *a1, u8 *a2);
extern void func_00261558(s32 a0, s32 a1);
extern void func_001EDC20(s32 a0, s32 a1);

s32 func_001EDB20(u8 *obj, s32 arg1) {
    s32 idx;

    __builtin_memset(obj, 0, 0x30);
    *(s32 *)(obj + 0x24) = arg1;
    idx = func_002623D8();
    if (idx < 0) {
        return -1;
    }
    func_0025E0B8(idx, *(u8 **)(D_00387A40 + 8) + idx * 0x1520, obj);
    func_00261558(idx & 0xFFFF, 0);
    func_001EDC20(idx, 0);
    return idx;
}
