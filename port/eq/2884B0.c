#include "common.h"

s32 sceMcGetInfo(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 sceMcSync(s32 arg0, s32 arg1, s32 arg2);
extern s32 gMcCardCmd;
extern u8 gMcCardPort[] __attribute__((section(".data")));

void McCard_GetInfoSync(s32 arg0) {
    s32 *s2;
    s32 off;

    off = arg0 * 0x24;
    s2 = (s32 *)(gMcCardPort + off + 8);
    *s2 = 0;
    gMcCardCmd = 0x18;
    *(s32 *)(gMcCardPort + off + 4) = sceMcGetInfo(arg0, 0, (s32)(gMcCardPort + off + 0xC), (s32)(gMcCardPort + off + 0x10), (s32)(gMcCardPort + off + 0x14));
    sceMcSync(0, 0, (s32)s2);
}
