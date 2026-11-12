#include "common.h"

void func_00297720(s32 arg0, s32 arg1);
void func_00297D78(s32 arg0, s32 arg1, s32 arg2);
s32 sceSdRemote(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 *D_00387ED0;

void func_00297978(s32 arg0, s32 arg1) {
    s32 temp_a0;

    func_00297720(arg0, arg1);
    temp_a0 = *(s32 *)(D_00387ED0 + 0x64);
    if (temp_a0 < 0) {
        return;
    }
    if (*(s32 *)(D_00387ED0 + 0x70) != 0) {
        if (sceSdRemote(1, 0x80F0, 1, 0) == 1) {
            *(s32 *)(D_00387ED0 + 0x70) = 0;
            *(s32 *)(D_00387ED0 + 0x64) = -1;
        }
    } else {
        func_00297D78(temp_a0, *(s32 *)(D_00387ED0 + 0x68), 1);
    }
}
