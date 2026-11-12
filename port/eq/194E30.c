#include "common.h"

/* 0x00194E30 (BT3 EftBlastObj_IsAlive, exact; record check is 0x194948 = EftBlastObj_Update): returns 1 if arg0 is non-null, arg0->0x28 points at a record whose first word is 0x00194948 (a vtable
 * check), and bit 0 of the word at arg0->0x38 + 0x60 is set; otherwise 0. */
s32 EftBlastObj_IsAlive(u8 *arg0) {
    u8 *p;

    if (arg0 == NULL) {
        return 0;
    }
    p = *(u8 **)(arg0 + 0x28);
    if (*(s32 *)p != 0x00194948) {
        return 0;
    }
    p = *(u8 **)(arg0 + 0x38);
    return (*(s32 *)(p + 0x60) & 1) != 0;
}
