#include "common.h"

void *memcpy(void *, const void *, unsigned int);
void *memset(void *, int, unsigned int);
void func_002974F8(s32 arg0, void *arg1);
extern u8 *gSndRpc;
extern u8 D_003B0E00 __attribute__((section(".data")));

/* 0x00297720: when byte gSndRpc+0x68 is non-zero: copies 0xC0 bytes from gSndRpc+0x68 to D_003B0E00, stores the
 * halfword at gSndRpc+0x128 after them, calls func_002974F8(0x40, D_003B0E00), then clears 0x100 bytes at
 * gSndRpc+0x68. */
void func_00297720(void) {
    if (gSndRpc[0x68] == 0) {
        return;
    }
    memcpy(&D_003B0E00, gSndRpc + 0x68, 0xC0);
    *(s16 *)(&D_003B0E00 + 0xC0) = *(s16 *)(gSndRpc + 0x128);
    func_002974F8(0x40, &D_003B0E00);
    memset(gSndRpc + 0x68, 0, 0x100);
}
