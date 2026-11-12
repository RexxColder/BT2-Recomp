#include "m2c_macros.h"

M2C_UNK StgRigid_Update();                          /* extern */
M2C_UNK func_001041A0(M2C_UNK);                     /* extern */
M2C_UNK func_001043A8(M2C_UNK);                     /* extern */
M2C_UNK func_00104570(M2C_UNK);                     /* extern */
M2C_UNK func_00104628(M2C_UNK);                     /* extern */
M2C_UNK func_0011AD58();                            /* extern */
M2C_UNK func_0011E988();                            /* extern */
M2C_UNK func_00126258();                            /* extern */
M2C_UNK func_001262A0();                            /* extern */
M2C_UNK func_00126688(s32);                         /* extern */
M2C_UNK func_001268E8();                            /* extern */
M2C_UNK func_001F71B0();                            /* extern */
M2C_UNK func_001F7860();                            /* extern */
M2C_UNK func_001F7FE0();                            /* extern */
M2C_UNK func_001F8420();                            /* extern */
M2C_UNK func_001F86F8();                            /* extern */
void *func_002112A0(M2C_UNK);                       /* extern */
M2C_UNK func_002423F8();                            /* extern */
M2C_UNK func_0025A4E0();                            /* extern */
s32 func_0025AB48();                                /* extern */
M2C_UNK func_0025BF08(s32);                         /* extern */
M2C_UNK func_0025BF98(M2C_UNK);                     /* extern */
M2C_UNK func_0025C058();                            /* extern */
M2C_UNK func_0025C098(s32);                         /* extern */
s32 func_0025C1B0();                                /* extern */
M2C_UNK func_00260F80();                            /* extern */
M2C_UNK func_00276F38();                            /* extern */
M2C_UNK func_00280E30();                            /* extern */
extern void *D_003876A0;

s32 func_00102AA0(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;

    var_s0 = 0;
    func_001F71B0();
    func_001F7860();
    func_00126258();
    func_00260F80();
    func_0011AD58();
    func_001262A0();
    func_001F7FE0();
    func_001268E8();
    func_0025BF08(0);
    func_0025C098(M2C_FIELD(func_002112A0(0), s32 *, 0x1534));
    func_0025BF08(1);
    func_0025C098(M2C_FIELD(func_002112A0(1), s32 *, 0x1534));
    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2)) {
        temp_v0 = func_0025C1B0();
        func_0025BF08((temp_v0 >= 0) ? temp_v0 : 0);
        func_0025C058();
    } else {
        temp_v0_2 = func_0025C1B0();
        if (temp_v0_2 >= 0) {
            var_s0 = 1;
            func_0025BF08(temp_v0_2);
            func_0025BF98(0);
            func_0025C058();
        }
    }
    if (func_0025AB48() != 0) {
        var_s0 = 1;
        func_0025BF98(0);
        func_0025C058();
        func_0025A4E0();
    }
    func_001F8420();
    func_001F86F8();
    func_0011E988();
    func_001041A0(0);
    func_001041A0(1);
    func_001043A8(0);
    func_001043A8(1);
    func_00104570(0);
    func_00104570(1);
    func_00104628(0);
    func_00104628(1);
    func_00276F38();
    StgRigid_Update();
    func_002423F8();
    func_00280E30();
    func_00126688(var_s0);
    return var_s0;
}
