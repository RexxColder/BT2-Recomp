#include "common.h"

void func_00191C00(void *arg0, void *arg1) {
    u8 *temp_v0;
    f32 temp_f0;

    temp_v0 = *(u8 **) ((u8 *) arg1 + 0x38);
    temp_f0 = *(f32 *) (temp_v0 + 0x20) * 30.0f;
    *(f32 *) ((u8 *) arg0 + 0x110) = temp_f0;
    *(f32 *) ((u8 *) arg0 + 0x114) = temp_f0 * *(f32 *) (temp_v0 + 0x24);
}
