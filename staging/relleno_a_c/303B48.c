#include "common.h"

extern s32 D_003605A0 __attribute__((section(".data")));
extern s32 D_003605A8 __attribute__((section(".data")));

/* 0x00303B48 Hud_Term (nombre heredado; es un Init con contador): D_003605A8++; la primera vez (== 1 tras
 * incrementar) pone D_003605A0 a 0. */
void Hud_Term(void) {
    D_003605A8 += 1;
    if (D_003605A8 == 1) {
        D_003605A0 = 0;
    }
}
