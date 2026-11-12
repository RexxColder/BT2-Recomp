#include "common.h"

void func_00297D78(s32 arg0, s32 arg1);
s32 sceSdRemote(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 *D_00387ED0;

s32 func_002980C0(void) {
    s32 a0 = *(s32 *)(D_00387ED0 + 0x64);

    if (a0 < 0) {
        return 1;
    }
    if (*(s32 *)(D_00387ED0 + 0x70) != 0) {
        s32 r = sceSdRemote(1, 0x80F0, 1, 0);

        if (r == 1) {
            *(s32 *)(D_00387ED0 + 0x70) = 0;
            *(s32 *)(D_00387ED0 + 0x64) = -1;
            return r;
        }
        return 0;
    }
    func_00297D78(a0, *(s32 *)(D_00387ED0 + 0x68));
    return 0;
}
