#include "common.h"

s32 func_0024C148(void);
extern u8 *D_003879A0;

/* table index: (D+0x1DC)*4 + 0x22*(D+0x1C8 + 7*(D+0x1CC)) + v; every use reloads D like the asm */
#define DP ((s32)D_003879A0)
#define IDX(v) (*(s32 *)(DP + 0x1DC) * 4 + (*(s32 *)(DP + 0x1C8) + *(s32 *)(DP + 0x1CC) * 7) * 0x22 + (v))

void func_0024C528(void) {
    s32 vA;
    s32 vB;
    s32 vC;
    s32 vD;
    s32 vE;
    s32 vF;
    s32 vG;
    s32 vH;
    s32 vI;
    s32 vJ;
    s32 vK;
    s32 s0;
    s32 t0;
    s32 v1;
    s32 h1;
    s32 h2;
    s32 h3;
    s32 h4;
    s32 h5;

    vA = func_0024C148();
    if (*(s16 *)(IDX(vA) + 0x1408) != 0) {
        vB = func_0024C148();
        vC = func_0024C148();
        h1 = *(s16 *)(IDX(vC) + 0x1408);
        *(u16 *)(vB + h1 * 4 + 0x1F2E) = (u16)(*(u16 *)(vB + h1 * 4 + 0x1F2E) + 1);
        vD = func_0024C148();
        h2 = *(s16 *)(IDX(vD) + 0x1408);
        s0 = *(s32 *)(DP + 0x334C) + h2 * 48;
        vE = func_0024C148();
        vF = func_0024C148();
        t0 = *(s32 *)(s0 - 0x30 + 0x10);
        h3 = *(s16 *)(IDX(vF) + 0x1408);
        v1 = *(s16 *)(h3 * 4 + vE + 0x1F2E);
        if (t0 < v1) {
            vG = func_0024C148();
            vH = func_0024C148();
            vI = func_0024C148();
            h4 = *(s16 *)(IDX(vI) + 0x1408);
            h5 = *(s16 *)(IDX(vH) + 0x1408);
            t0 = *(s32 *)(DP + 0x334C) + h4 * 48;
            *(s16 *)(vG + h5 * 4 + 0x1F2E) = (s16)*(u16 *)(t0 - 0x20);
        }
    }

    vJ = func_0024C148();
    *(s16 *)(IDX(vJ) + 0x1408) = 0;
    vK = func_0024C148();
    *(s16 *)(IDX(vK) + 0x140A) = 0;
}
