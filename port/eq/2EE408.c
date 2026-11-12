#include "common.h"

s32 func_0032EB60(s32 arg0, s32 arg1);
s32 func_0032EBF0(s32 arg0, s32 arg1);

s32 func_002EE408(s32 arg0) {
    s32 sp[12];
    s32 var_s1;

    var_s1 = 0;
    if (arg0 == 0) {
        return 0;
    }
    func_0032EB60(arg0, (s32)sp);
    if (sp[0] == 8 || sp[0] == 0xC) {
        var_s1 = func_0032EBF0(arg0, 0xC);
    }
    return var_s1;
}
