#include "common.h"

u8 *func_002768D8(s32 arg0);
void func_00129C28(void *arg0, void *arg1);
extern u8 *D_00387E9C;

void Fade_UpdateAll(void) {
    f32 sp[4];
    u8 *temp;

    if (D_00387E9C != NULL) {
        temp = func_002768D8(5);
        if (temp != NULL) {
            sp[0] = (f32)temp[1];
            sp[1] = (f32)temp[2];
            sp[2] = (f32)temp[3];
            sp[3] = (f32)temp[4];
            D_00387E9C[0x1491] = temp[0];
        } else {
            sp[0] = 128.0f;
            sp[1] = 128.0f;
            sp[2] = 128.0f;
            sp[3] = 128.0f;
            D_00387E9C[0x1491] = 0;
        }
        func_00129C28(D_00387E9C + 0x14A0, sp);
    }
}
