#include "common.h"

void func_002F8E58(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F8EB8(s32 arg0);

// Calls func_002F8E58 on the record at arg0+0x48 (args: *(arg0+8), *(+0x48), arg1 * 2,
// *(+0x14) + *(+0x20) * 2, that + *(+0x1C) * 2), then func_002F8EB8 on *(arg0+8).
void func_002E8008(s32 arg0, s32 arg1) {
    u8 *rec = (u8 *)arg0 + 0x48;
    s32 scaled = arg1 * 2;
    s32 base = *(s32 *)(rec + 0x14) + (*(s32 *)(rec + 0x20) * 2);
    s32 first = *(s32 *)rec;
    s32 extra = *(s32 *)(rec + 0x1C);
    s32 owner = *(s32 *)((u8 *)arg0 + 8);
    func_002F8E58(owner, first, scaled, base, base + (extra * 2));
    func_002F8EB8(owner);
}
