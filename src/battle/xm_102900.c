#include "m2c_macros.h"

void func_00101BF0(void);
void func_00102568(void);
void func_00104C10(s32, s32, s32);
void func_00104E60(void);
void func_00297A30(void);
void func_002998D8(void);
void func_002A85B0(void);
void *memset(void *, int, unsigned int);
extern void *D_003876A0;

// Re-initialises the object at D_003876A0: clears its first 0x70 bytes, runs four setup steps, calls func_00104C10 with three of its fields, then two more steps and a tail call to func_00102568.
void func_00102900(void) {
    memset(D_003876A0, 0, 0x70);
    func_00101BF0();
    func_00297A30();
    func_002A85B0();
    func_00104C10(M2C_FIELD(D_003876A0, s32 *, 0xD4), M2C_FIELD(D_003876A0, s32 *, 0x2AC), M2C_FIELD(D_003876A0, s32 *, 0x47C));
    func_00104E60();
    func_002998D8();
    func_00102568();
}
