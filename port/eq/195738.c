#include "common.h"

s32 BtlCharApi_IsInTechnique(s32 arg0);
void Mem_ReadU16(s32 arg0, s32 arg1);
s32 func_00195220(s32 arg0);
void func_00195598(s32 arg0);
void func_001957F8(s32 arg0, s32 arg1);
s32 func_0020B070(s32 arg0);

void func_00195738(s32 arg0, s32 arg1) {
    s32 s0;
    s32 t;

    s0 = 0;
    func_00195598(arg0);
    do {
        if (func_0020B070(s0) != 0) {
            t = s0;
            {
                s32 tech_ = BtlCharApi_IsInTechnique(s0);
                if (tech_ != 0) {
                    s0 += 1;
                    func_001957F8(t, 0);
                } else {
                    s0 += 1;
                    Mem_ReadU16(t, 0);
                }
            }
        } else {
            if (func_00195220(s0) == 0) {
                func_001957F8(s0, arg1);
            }
            s0 += 1;
        }
    } while (s0 < 2);
}
