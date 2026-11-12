#include "common.h"

void func_0018DE18(f32 *arg0, f32 farg0, f32 farg1) {
    f32 var_f0;

    var_f0 = *arg0;
    if (farg1 < var_f0) {
        *arg0 = farg1;
        var_f0 = farg1;
    }
    if (var_f0 < farg0) {
        *arg0 = farg0;
    }
}
