#include "common.h"

extern u8 *D_004279D0 __attribute__((section(".data")));

void func_29C1E8(s32 arg0);
void func_29C550(s32 arg0);
s32 func_29C640(s32 arg0);
void func_29C7C0(s32 arg0);
void func_29C800(s32 arg0);
void func_29C820(s32 arg0);
s32 func_29C830(void);

/* 0x003E8110: state machine on G->0x31C (G = D_004279D0). 1: func_29C7C0(1), func_29C550(0); if G->0x324 > 0 then
 * G->0x320-- and once it goes negative G->0x320 = 0x78, G->0x31C = 2; G->0x324 < 0: func_29C820(1) then the same
 * 0x78/2 update; G->0x324 == 0: G->0x324 = func_29C640(0), G->0x320 = 0xC. 2: func_29C7C0(0), func_29C550(1),
 * func_29C640(0), G->0x31C = 3. 3: func_29C640(0); if func_29C830() G->0x31C = 0. Then func_29C800(0x23) and the
 * tail call func_29C1E8(1). */
void func_003E8110(void) {
    s32 v;

    v = *(s32 *)(D_004279D0 + 0x31C);
    if (v == 0) {
        return;
    }
    if (v == 2) {
        func_29C7C0(0);
        func_29C550(1);
        func_29C640(0);
        *(s32 *)(D_004279D0 + 0x31C) = 3;
    } else if (v == 1) {
        func_29C7C0(1);
        func_29C550(0);
        if (*(s32 *)(D_004279D0 + 0x324) > 0) {
            *(s32 *)(D_004279D0 + 0x320) = *(s32 *)(D_004279D0 + 0x320) - 1;
            if (*(s32 *)(D_004279D0 + 0x320) < 0) {
                *(s32 *)(D_004279D0 + 0x320) = 0x78;
                *(s32 *)(D_004279D0 + 0x31C) = 2;
            }
        } else if (*(s32 *)(D_004279D0 + 0x324) < 0) {
            func_29C820(1);
            *(s32 *)(D_004279D0 + 0x320) = 0x78;
            *(s32 *)(D_004279D0 + 0x31C) = 2;
        } else {
            *(s32 *)(D_004279D0 + 0x324) = func_29C640(0);
            *(s32 *)(D_004279D0 + 0x320) = 0xC;
        }
    } else if (v == 3) {
        func_29C640(0);
        if (func_29C830() != 0) {
            *(s32 *)(D_004279D0 + 0x31C) = 0;
        }
    }
    func_29C800(0x23);
    func_29C1E8(1);
}
