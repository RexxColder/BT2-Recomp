#include "common.h"

void *memset(void *dst, s32 c, u32 n);
extern s32 D_003605E0 __attribute__((section(".data")));
extern u8 D_003605E8[] __attribute__((section(".data")));

/* 0x00303C78 BtlPause_Term: Init con contador: si D_003605E0 == 0 limpia D_003605E8 (0x480 bytes); siempre D_003605E0++. */
void BtlPause_Term(void) {
    if (D_003605E0 == 0) {
        memset(D_003605E8, 0, 0x480);
    }
    D_003605E0 += 1;
}
