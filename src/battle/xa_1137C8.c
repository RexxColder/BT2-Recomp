#include "common.h"

/* Per-record handler (the original's func_00113620, 0x113620; the record and the argument are passed on). */
extern void func_00113620(s32 *rec, s32 arg);

/* Walks count records of 0x60 bytes from base; each one whose first word has bit 0 set goes to the handler. */
void BtlRec_CallFlagged(s32 *base, s32 arg, s32 count) {
    s32 *rec;
    s32 n;

    if (count > 0) {
        rec = base;
        n = count;
        do {
            if (*rec & 1) {
                func_00113620(rec, arg);
            }
            n -= 1;
            rec = (s32 *)((u8 *)rec + 0x60);
        } while (n != 0);
    }
}
