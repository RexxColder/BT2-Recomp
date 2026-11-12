#include "common.h"

extern s32 D_00354ECC;
extern s32 D_00354ED4;
extern u8 D_0034AEE0[];
void func_002E93C0();
void func_002E93D8(void);
void func_002F12C8(void);
void func_002F8A78(u8 *arg0);
void func_002EFEB8(void);

/* 0x002F5D10: state machine on D_00354ECC: if it is nonzero, tail call func_002E93D8. Else state 1, calls, state 2, then
 * for the 16 records of 0xC8 bytes at D_0034AEE0 whose first byte is 1: func_002F8A78(record); state 3, func_002EFEB8(),
 * again when D_00354ED4 < 0x33; state 0; tail call func_002E93D8. */
void func_002F5D10(unsigned long r_a0, unsigned long r_a1, unsigned long r_a2, unsigned long r_a3, unsigned long r_t0, unsigned long r_t1, unsigned long r_t2, unsigned long r_t3) { /* asm: a0, a1, a2, a3, t0, t1, t2, t3 arrive and pass through untouched */
    s32 k;
    u8 *e;

    func_002E93C0(r_a0, r_a1, r_a2, r_a3, r_t0, r_t1, r_t2, r_t3);
    if (D_00354ECC != 0) {
        func_002E93D8();
        return;
    }
    D_00354ECC = 1;
    func_002E93D8();
    func_002E93C0(r_a0, r_a1, r_a2, r_a3, r_t0, r_t1, r_t2, r_t3);
    func_002F12C8();
    D_00354ECC = 2;
    e = D_0034AEE0;
    for (k = 0; k < 16; k++) {
        if (*(signed char *)e == 1) {
            func_002F8A78(e);
        }
        e += 0xC8;
    }
    D_00354ECC = 3;
    func_002EFEB8();
    if (D_00354ED4 < 0x33) {
        func_002EFEB8();
    }
    D_00354ECC = 0;
    func_002E93D8();
}
