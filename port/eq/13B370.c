#include "common.h"

extern u8 *gEftDust;
extern u8 *D_003876A0;

/* 0x0013B370(i, mode): 0 when gEftDust is NULL or bit 1 of the 64-bit word at D_003876A0 +0x4D8 is set. Else the
 * record at gEftDust->table + 12 * i: mode 0 claims it when its byte +8 is clear (word 0 = i, byte 8 = 1, word 4 = 0);
 * mode 1 releases it when byte +8 is set (byte 8 = 0, word 4 = 0). Returns 1 in every other case. */
s32 func_0013B370(s32 arg0, s32 arg1) {
    u8 *rec;
    u8 mode = (u8)arg1;

    if (gEftDust == NULL) {
        return 0;
    }
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x2) != 0) {
        return 0;
    }
    rec = *(u8 **)gEftDust + arg0 * 12;
    if (mode == 0) {
        if (rec[8] == 0) {
            *(s32 *)rec = arg0;
            rec[8] = 1;
            *(s32 *)(rec + 4) = 0;
        }
        return 1;
    }
    if (mode == 1) {
        if (rec[8] != 0) {
            rec[8] = 0;
            *(s32 *)(rec + 4) = 0;
        }
        return 1;
    }
    return 1;
}
