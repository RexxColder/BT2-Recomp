#include "common.h"

void DemoCam_PlayStageAnim(s32 arg0);

/* 0x00109BE8(obj): switch on the byte at obj+8: 0 plays stage anim 0, 2 plays 1, 4 plays 2 (each followed by the byte
 * at obj+8 incremented); every other value (1, 3, 5, 6 and 7 and up) does nothing. Returns 0. */
s32 func_00109BE8(u8 *arg0) {
    s32 k;

    switch (arg0[8]) {
        case 0:
            k = 0;
            break;
        case 2:
            k = 1;
            break;
        case 4:
            k = 2;
            break;
        default:
            return 0;
    }
    DemoCam_PlayStageAnim(k);
    arg0[8] = (u8)(arg0[8] + 1);
    return 0;
}
