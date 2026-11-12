#include "common.h"

s32 sceMcGetInfo(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 sceMcSync(s32 arg0, s32 arg1, s32 arg2);
extern s32 gMcCardCmd;
extern u8 gMcCardPort[] __attribute__((section(".data")));

void McCard_Probe(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;

    temp_s0 = arg0 * 0x24;
    temp_s1 = (s32)gMcCardPort + temp_s0 + 8;
    gMcCardCmd = 0x19;
    *(s32 *)temp_s1 = 0;
    *(s32 *)((s32)gMcCardPort + temp_s0 + 4) = sceMcGetInfo(arg0, 0, 0, 0, 0);
    sceMcSync(0, 0, temp_s1);
}
