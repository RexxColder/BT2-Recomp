#include "common.h"

f32 func_00270F40(s32 arg0, s32 arg1);

f32 func_0026F148(void *arg0, s32 *arg1) {
    if (*arg1 >= 0) {
        return func_00270F40(*(s32 *)((u8 *)arg0 + 0x1C), (s32)arg1);
    }
    return 0.0f;
}
