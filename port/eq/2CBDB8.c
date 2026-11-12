#include "common.h"

s32 func_0032ECA0(s32 arg0);
s32 func_0032EC80(s32 arg0, s32 arg1);

void func_002CBDB8(s32 arg0) {
    s32 v1;
    s32 v0;
    s32 flag;

    func_0032ECA0(*(s32 *)((u8 *)arg0 + 0x40));
    v1 = *(s32 *)((u8 *)arg0 + 0x14);
    v0 = v1 + 0x803;
    flag = v0 < 0;
    *(s32 *)((u8 *)arg0 + 0x14) = ((flag != 0 ? v1 + 0x1002 : v0) >> 11) << 11;
    func_0032EC80(*(s32 *)((u8 *)arg0 + 0x40), flag);
}
