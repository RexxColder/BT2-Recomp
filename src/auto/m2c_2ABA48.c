#include "m2c_macros.h"

M2C_UNK ObjOutline_Term_25A468();                   /* extern */
M2C_UNK func_001012D0();                            /* extern */
M2C_UNK func_00102348();                            /* extern */
M2C_UNK func_002596F0();                            /* extern */
M2C_UNK func_0025BA20();                            /* extern */
M2C_UNK func_0025E5D8();                            /* extern */
M2C_UNK func_00261D10();                            /* extern */
M2C_UNK func_002738F0();                            /* extern */
M2C_UNK func_00278D40();                            /* extern */
M2C_UNK func_00280DE8();                            /* extern */
M2C_UNK func_00284AC8();                            /* extern */
M2C_UNK func_0028B218();                            /* extern */
M2C_UNK func_0028BB60(s32);                         /* extern */
M2C_UNK func_0028BCE8();                            /* extern */
M2C_UNK func_00297A30();                            /* extern */
M2C_UNK func_00297EC8();                            /* extern */
M2C_UNK func_0029F1E0();                            /* extern */
M2C_UNK func_002A8648();                            /* extern */
M2C_UNK func_002ACEF8();                            /* extern */
extern void *D_003876A0;

void func_002ABA48(unsigned long r_a0, unsigned long r_a1, unsigned long r_a2, unsigned long r_a3, unsigned long r_t0, unsigned long r_t1, unsigned long r_t2, unsigned long r_t3) { /* asm: a0, a1, a2, a3, t0, t1, t2, t3 arrive and pass through untouched */
    void *temp_s0;

    temp_s0 = D_003876A0;
    func_002ACEF8(r_a0, r_a1, r_a2, r_a3, r_t0, r_t1, r_t2, r_t3);
    func_002596F0();
    func_0029F1E0();
    ObjOutline_Term_25A468();
    func_00278D40();
    func_00280DE8();
    func_0025E5D8();
    func_0025BA20();
    func_002738F0();
    func_00261D10();
    func_002A8648();
    func_00284AC8();
    func_00102348();
    func_00297EC8();
    func_00297EC8();
    func_00297EC8();
    func_0028BCE8();
    func_00297A30();
    func_001012D0();
    func_0028BB60(M2C_FIELD(temp_s0, s32 *, 0xC));
    func_0028BB60(M2C_FIELD(temp_s0, s32 *, 0x14));
    func_0028BB60(M2C_FIELD(temp_s0, s32 *, 0x24));
    func_0028BB60(M2C_FIELD(temp_s0, s32 *, 0x28));
    func_0028B218();
    M2C_FIELD(D_003876A0, s64 *, 0x4D8) = (s64) (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & ~8);
}
