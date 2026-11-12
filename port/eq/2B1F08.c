#include "common.h"

f32 Mathf_Asin(f32 arg0);
f32 atan2f(f32 arg0, f32 arg1);
void func_002B20E0(s32 arg0);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void sceVu0Normalize(s32 arg0, s32 arg1);
extern f32 D_00387648;
extern f32 D_0038764C;
extern f32 D_00387650;
extern f32 D_00387654;

void func_002B1F08(u8 *arg0) {
    s32 buf[8];
    f32 *vec;
    f32 f0;
    f32 a10;
    f32 a18;

    vec = (f32 *)&buf[4];
    if (*(s32 *)(arg0 + 0x1C) >= 0) {
        func_002B20E0((s32)buf);
        func_00312650((s32)vec, (s32)buf, (s32)(arg0 + 0xD0));
        a10 = vec[0] < 0.0f ? -vec[0] : vec[0];
        a18 = vec[2] < 0.0f ? -vec[2] : vec[2];
        if (D_00387648 < a10 || D_00387648 < a18) {
            sceVu0Normalize((s32)vec, (s32)vec);
            *(f32 *)(arg0 + 0x70) = atan2f(vec[0], vec[2]);
            f0 = Mathf_Asin(vec[1]) + D_0038764C;
            *(f32 *)(arg0 + 0x15C) = *(f32 *)(arg0 + 0x70);
        } else if (0.0f < vec[1]) {
            f0 = D_00387650;
        } else {
            f0 = D_00387654;
        }
        *(f32 *)(arg0 + 0x74) = f0;
    }
}
