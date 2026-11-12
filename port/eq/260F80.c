#include "common.h"

s32 func_002ADF38(u8 *arg0);
void func_00260BF8(u8 *arg0, s32 arg1);
void func_0025FFB8(u8 *arg0);
void func_0025F2A0(u8 *arg0);
void func_0025F5F8(u8 *arg0);
void func_00260D48(u8 *arg0);
void BtlMove_UpdateAction(u8 *arg0);
void func_00260638(u8 *arg0);
extern u8 *D_003876A0;
extern u8 *D_00387A40;

/* 0x00260F80: unless flag 0x100 of D_003876A0+0x4D8 is set, walk the D_00387A40 table (count at +0xC, base at
 * +8, 0x1520-byte records): a record with word +0xC != 0 whose func_002ADF38 check returns 0 gets its update
 * chain run (00260BF8(rec, 0) then the other calls with rec only). */
void func_00260F80(void) {
    s32 i;
    u8 *s0;

    if (*(s32 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }
    for (i = 0; i < *(s32 *)(D_00387A40 + 0xC); i++) {
        s0 = (u8 *)(*(s32 *)(D_00387A40 + 8) + i * 0x1520);
        if (*(s32 *)(s0 + 0xC) != 0) {
            if (func_002ADF38(s0) == 0) {
                func_00260BF8(s0, 0);
                func_0025FFB8(s0);
                func_0025F2A0(s0);
                func_0025F5F8(s0);
                func_00260D48(s0);
                BtlMove_UpdateAction(s0);
                func_00260D48(s0);
                func_00260638(s0);
            }
        }
    }
}
