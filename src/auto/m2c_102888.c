#include "m2c_macros.h"

M2C_UNK BtlCam_Term();                              /* extern */
M2C_UNK BtlScene_Term();                            /* extern */
M2C_UNK ObjOutline_Term_25A468();                   /* extern */
M2C_UNK ScrWarp_Term();                             /* extern */
M2C_UNK StgRigid_Term();                            /* extern */
M2C_UNK func_001056D8();                            /* extern */
M2C_UNK func_0011E928();                            /* extern */
M2C_UNK func_001F6CF8();                            /* extern */
M2C_UNK func_0025E5D8();                            /* extern */
M2C_UNK func_002720B8();                            /* extern */
M2C_UNK func_00278D40();                            /* extern */
M2C_UNK func_00280DE8();                            /* extern */
M2C_UNK func_00284AC8();                            /* extern */

void func_00102888(void) {
    ScrWarp_Term();
    StgRigid_Term();
    func_002720B8();
    func_00280DE8();
    BtlCam_Term();
    ObjOutline_Term_25A468();
    BtlScene_Term();
    func_0011E928();
    func_001F6CF8();
    func_0025E5D8();
    func_00278D40();
    func_001056D8();
    func_00284AC8();
}
