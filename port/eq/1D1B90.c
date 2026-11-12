#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
f32 Mathf_Cos(f32 arg0);
f32 func_0012A3F8(f32 arg0);
void func_001D9040(void *arg0, void *arg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
void func_002088F0(s32 arg0, void *arg1);
void func_00208798(s32 arg0, void *arg1);
extern u8 *D_00387E9C;

s32 func_001D1B90(s32 arg0, f32 farg0) {
    s32 sp[12];
    f32 h;
    s32 var_v0;

    var_v0 = 0;
    if (D_00387E9C[0x1491] != 0) {
        func_002088F0(arg0, &sp[4]);
        func_00208798(arg0, &sp[8]);
        *(f32 *)&sp[0] = func_0012A3F8(*(f32 *)&sp[5]);
        sp[1] = 0;
        *(f32 *)&sp[2] = Mathf_Cos(*(f32 *)&sp[5]);
        *(f32 *)&sp[3] = 1.0f;
        h = BtlCharApi_GetHeight(arg0);
        func_001D9040(&sp[8], sp, 45.0f, 80.0f, h, farg0);
        h = BtlCharApi_GetHeight(arg0);
        func_001D9040(&sp[8], sp, -45.0f, 80.0f, h, farg0);
        var_v0 = 1;
    }
    return var_v0;
}
