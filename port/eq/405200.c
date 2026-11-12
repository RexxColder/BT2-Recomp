#include "common.h"

extern u8 *D_0042BB70 __attribute__((section(".data")));

void func_29C1E8(s32 arg0);
void func_29C550(s32 arg0);
s32 func_29C640(s32 arg0);
void func_29C7C0(s32 arg0);
void func_29C800(s32 arg0);
void func_29C820(s32 arg0);
s32 func_29C830(void);

/* 0x00405200: state machine on G->0x364 (G = D_0042BB70). 1: func_29C7C0(1), func_29C550(0); if G->0x36C > 0 then
 * G->0x368-- and once it goes negative G->0x368 = 0x78, G->0x364 = 2; G->0x36C < 0: func_29C820(1) then the same
 * 0x78/2 update; G->0x36C == 0: G->0x36C = func_29C640(0), G->0x368 = 0xC. 2: func_29C7C0(0), func_29C550(1),
 * func_29C640(0), G->0x364 = 3. 3: func_29C640(0); if func_29C830() G->0x364 = 0. Then func_29C800(0xF) and the
 * tail call func_29C1E8(1). */
void func_00405200(void) {
    s32 v;

    v = *(s32 *)(D_0042BB70 + 0x364);
    if (v == 0) {
        return;
    }
    if (v == 2) {
        func_29C7C0(0);
        func_29C550(1);
        func_29C640(0);
        *(s32 *)(D_0042BB70 + 0x364) = 3;
    } else if (v == 1) {
        func_29C7C0(1);
        func_29C550(0);
        if (*(s32 *)(D_0042BB70 + 0x36C) > 0) {
            *(s32 *)(D_0042BB70 + 0x368) = *(s32 *)(D_0042BB70 + 0x368) - 1;
            if (*(s32 *)(D_0042BB70 + 0x368) < 0) {
                *(s32 *)(D_0042BB70 + 0x368) = 0x78;
                *(s32 *)(D_0042BB70 + 0x364) = 2;
            }
        } else if (*(s32 *)(D_0042BB70 + 0x36C) < 0) {
            func_29C820(1);
            *(s32 *)(D_0042BB70 + 0x368) = 0x78;
            *(s32 *)(D_0042BB70 + 0x364) = 2;
        } else {
            *(s32 *)(D_0042BB70 + 0x36C) = func_29C640(0);
            *(s32 *)(D_0042BB70 + 0x368) = 0xC;
        }
    } else if (v == 3) {
        func_29C640(0);
        if (func_29C830() != 0) {
            *(s32 *)(D_0042BB70 + 0x364) = 0;
        }
    }
    func_29C800(0xF);
    func_29C1E8(1);
}
