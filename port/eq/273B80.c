#include "common.h"

f32 func_0025B738(void *arg0);

/* a0 (posicion) pasa tal cual a 25B738; f12 es el valor a atenuar */
f32 func_00273B80(void *pos, f32 arg0) {
    f32 temp_f0;
    f32 var_f0;
    f32 var_f2;

    temp_f0 = func_0025B738(pos);
    var_f0 = 0.0f;
    if (!(temp_f0 <= 0.0f)) {
        var_f0 = arg0;
        if (!(temp_f0 > 100.0f)) {
            if (!(temp_f0 > 75.0f)) {
                var_f2 = 0.0f;
            } else {
                var_f2 = ((temp_f0 - 75.0f) / 25.0f) * arg0;
            }
            var_f0 = var_f2;
        }
    }
    return var_f0;
}
