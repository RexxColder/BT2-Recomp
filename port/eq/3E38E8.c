#include "common.h"

extern u8 *D_004279C8 __attribute__((section(".data")));

void func_29C1E8(s32 arg0);
void func_29C550(s32 arg0);
s32 func_29C640(s32 arg0);
void func_29C7C0(s32 arg0);
void func_29C800(s32 arg0);
void func_29C820(s32 arg0);
s32 func_29C830(void);

/* 0x003E38E8: state machine on G->0x378 (G = D_004279C8). 1: func_29C7C0(1), func_29C550(0); if G->0x380 > 0 then
 * G->0x37C-- and once it goes negative G->0x37C = 0x78, G->0x378 = 2; G->0x380 < 0: func_29C820(1) then the same
 * 0x78/2 update; G->0x380 == 0: G->0x380 = func_29C640(0), G->0x37C = 0xC. 2: func_29C7C0(0), func_29C550(1),
 * func_29C640(0), G->0x378 = 3. 3: func_29C640(0); if func_29C830() G->0x378 = 0. Then func_29C800(0x23) and the
 * tail call func_29C1E8(1). */
void func_003E38E8(void) {
    s32 v;

    v = *(s32 *)(D_004279C8 + 0x378);
    if (v == 0) {
        return;
    }
    if (v == 2) {
        func_29C7C0(0);
        func_29C550(1);
        func_29C640(0);
        *(s32 *)(D_004279C8 + 0x378) = 3;
    } else if (v == 1) {
        func_29C7C0(1);
        func_29C550(0);
        if (*(s32 *)(D_004279C8 + 0x380) > 0) {
            *(s32 *)(D_004279C8 + 0x37C) = *(s32 *)(D_004279C8 + 0x37C) - 1;
            if (*(s32 *)(D_004279C8 + 0x37C) < 0) {
                *(s32 *)(D_004279C8 + 0x37C) = 0x78;
                *(s32 *)(D_004279C8 + 0x378) = 2;
            }
        } else if (*(s32 *)(D_004279C8 + 0x380) < 0) {
            func_29C820(1);
            *(s32 *)(D_004279C8 + 0x37C) = 0x78;
            *(s32 *)(D_004279C8 + 0x378) = 2;
        } else {
            *(s32 *)(D_004279C8 + 0x380) = func_29C640(0);
            *(s32 *)(D_004279C8 + 0x37C) = 0xC;
        }
    } else if (v == 3) {
        func_29C640(0);
        if (func_29C830() != 0) {
            *(s32 *)(D_004279C8 + 0x378) = 0;
        }
    }
    func_29C800(0x23);
    func_29C1E8(1);
}
