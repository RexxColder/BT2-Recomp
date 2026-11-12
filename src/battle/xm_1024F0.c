#include "m2c_macros.h"

void *func_001020F0(void);
void func_00261D10(void);
void func_0028BB60(void *);
extern s32 *D_003876A0;

// Releases the sub-objects held by the global object D_003876A0 (pointers at +0, +4, +0x24, +0xC, +0x30, +0x2C), then calls two cleanup routines.
void func_001024F0(void) {
    s32 *temp_s0;
    void *temp_v0;
    void *temp_a0;

    temp_s0 = D_003876A0;
    func_0028BB60(M2C_FIELD(temp_s0, void **, 0));
    func_0028BB60(M2C_FIELD(temp_s0, void **, 4));
    M2C_FIELD(temp_s0, s32 *, 4) = 0;
    func_0028BB60(M2C_FIELD(temp_s0, void **, 0x24));
    func_0028BB60(M2C_FIELD(temp_s0, void **, 0xC));
    temp_v0 = M2C_FIELD(temp_s0, void **, 0x30);
    if (temp_v0 != NULL) {
        func_0028BB60(temp_v0);
    }
    temp_a0 = M2C_FIELD(temp_s0, void **, 0x2C);
    if (temp_a0 != NULL) {
        func_0028BB60(temp_a0);
        M2C_FIELD(temp_s0, s32 *, 0x2C) = 0;
    }
    func_00261D10();
    func_001020F0();
}
