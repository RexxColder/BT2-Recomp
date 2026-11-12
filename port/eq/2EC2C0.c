#include "common.h"

void func_002EA050(void *arg0);
void func_002EA2F0(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4);
void func_002F2108(s32 arg0);
extern s32 D_0037BF90 __attribute__((section(".data")));
extern s32 D_0037BFB8 __attribute__((section(".data")));

s32 func_002EC2C0(u8 *arg0) {
    s32 temp_a0;
    s8 temp_v1;

    func_002EA2F0(7, 0, arg0, -1, -1);
    if (arg0 == NULL) {
        func_002EA050((void *)&D_0037BF90);
        return -3;
    }
    temp_v1 = *(s8 *)(arg0 + 1);
    if (temp_v1 != 1) {
        if (temp_v1 != 3) {
            temp_a0 = *(s32 *)(arg0 + 4);
            if (temp_a0 == 0) {
                func_002EA050((void *)&D_0037BFB8);
                return -1;
            }
            func_002F2108(temp_a0);
            *(s8 *)(arg0 + 3) = 1;
            func_002EA2F0(7, 1, arg0, -1, -1);
            return *(s32 *)(arg0 + 0x18);
        }
        *(s8 *)(arg0 + 1) = 1;
    }
    return *(s32 *)(arg0 + 0x18);
}
