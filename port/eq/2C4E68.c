#include "common.h"

void func_002DC680(s32 arg0, s32 arg1);
void func_002DC6E8(s32 arg0, s32 arg1, s32 arg2);

void func_002C4E68(u8 *arg0) {
    s32 sp[4];
    s32 sp10[8];
    s32 temp_s0;
    u8 *temp_s1;
    u8 *temp_s2;

    temp_s1 = arg0 + 0x90C;
    temp_s2 = (u8 *)*(s32 *)(arg0 + 0x1F7C);
    temp_s0 = *(s32 *)temp_s2;
    func_002DC680(temp_s0, (s32)sp);
    if (sp[3] > 0) {
        *(s32 *)(temp_s1 + 0x18) = sp[3];
    }
    func_002DC6E8(temp_s0, (s32)sp10, 1);
    if (sp10[4] != -1) {
        *(s32 *)(temp_s1 + 0x1C) = sp10[4];
    }
    if (*(s32 *)(temp_s1 + 0x24) == -1) {
        *(s32 *)(temp_s1 + 0x24) = *(s32 *)(temp_s2 + 8);
    }
    if (*(s32 *)(temp_s1 + 0x28) == -1) {
        *(s32 *)(temp_s1 + 0x28) = *(s32 *)(temp_s2 + 4);
    }
}
