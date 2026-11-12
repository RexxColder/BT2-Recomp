#include "common.h"

s32 func_002CDBB8(s32 arg0);
s32 func_002CDC28(s32 arg0);
s32 func_002CDCF0(s32 arg0);
s32 func_002CDD48(s32 arg0);
void func_002CDE40(s32 arg0);

void func_002CDB38(s32 arg0) {
    if (func_002CDBB8(arg0) == 0 && func_002CDC28(arg0) == 0 && func_002CDCF0(arg0) == 0) {
        if (func_002CDD48(arg0) == 0) {
            if (*(s32 *)(arg0 + 0x60) == 0) {
                return;
            }
        } else {
            func_002CDE40(arg0);
            return;
        }
    }
    func_002CDE40(arg0);
}
