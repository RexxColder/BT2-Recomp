#include "common.h"

void func_002F8E28(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F8EB8(s32 arg0);

// Calls func_002F8E28 on the record at arg0+0x48 (args: *(arg0+8), *(+0x48), arg1,
// *(+0x48+0x14) + *(+0x48+0x20) * 2, 0), then func_002F8EB8 on *(arg0+8).
void func_002E7FB8(s32 arg0, s32 arg1) {
    u8 *rec = (u8 *)arg0 + 0x48;
    s32 off = *(s32 *)(rec + 0x20);
    s32 owner = *(s32 *)((u8 *)arg0 + 8);
    s32 base = *(s32 *)(rec + 0x14);
    s32 first = *(s32 *)rec;
    func_002F8E28(owner, first, arg1, base + (off * 2), 0);
    func_002F8EB8(owner);
}
