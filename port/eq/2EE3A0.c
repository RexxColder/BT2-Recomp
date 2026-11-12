#include "common.h"

void func_0032EB60(s32 arg0, s32 arg1);
void func_0032EB90(s32 arg0, s32 arg1);

void func_002EE3A0(s32 arg0) {
    s32 sp[12];

    if (arg0 != 0) {
        func_0032EB60(arg0, (s32)sp);
        if ((sp[0] == 4) || (sp[0] == 0xC)) {
            func_0032EB90(arg0, 0xC);
        }
    }
}
