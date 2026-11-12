#include "common.h"

void func_0032EB70(s32 arg0, s32 arg1);
void iWakeupThread(s32 arg0, s32 arg1);

void func_002EE350(s32 arg0) {
    s32 sp[12];

    if (arg0 != 0) {
        func_0032EB70(arg0, (s32)sp);
        if ((sp[0] == 4) || (sp[0] == 0xC)) {
            iWakeupThread(arg0, 0xC);
        }
    }
}
