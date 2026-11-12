#include "common.h"

void func_002D7608(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D78A8(u8 *arg0, s32 arg1, s32 arg2);
void func_002D7938(u8 *arg0, s32 arg1, s32 arg2);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_002D77B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void (*temp_v0)(f32, f32, s32, s32);
    s32 temp_s3;

    temp_s3 = arg3 + 0x400;
    memset((void *)arg3, 0, 0x400);
    func_002D7608(arg0, arg1, arg2, temp_s3);
    temp_v0 = *(void (**)(f32, f32, s32, s32))(arg0 + 0x44);
    if (temp_v0 == NULL) {
        if (*(s32 *)(arg0 + 4) == 0x10) {
            func_002D78A8(arg0, temp_s3, arg3);
            return;
        }
        func_002D7938(arg0, temp_s3, arg3);
        return;
    }
    temp_v0(*(f32 *)(arg0 + 0x3C), *(f32 *)(arg0 + 0x40), temp_s3, arg3);
}
