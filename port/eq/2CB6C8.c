#include "common.h"

void func_0032ECA0(s32 arg0);
void func_0032EC80(s32 arg0);

s32 func_002CB6C8(s32 arg0, s32 arg1) {
    s32 temp_v1;

    func_0032ECA0(*(s32 *) (arg0 + 0x40));
    temp_v1 = *(s32 *) (arg0 + 0x14) - arg1;
    *(s32 *) (arg0 + 0x14) = temp_v1;
    *(s64 *) (arg0 + 0x48) = *(s64 *) (arg0 + 0x48) - (s64) arg1;
    if (temp_v1 < 0) {
        for (;;) {
        }
    }
    func_0032EC80(*(s32 *) (arg0 + 0x40));
    return arg1;
}
