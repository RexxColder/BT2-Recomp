#include "common.h"

s32 BtlCharApi_IsHidden(s32 arg0);
s32 BtlCharApi_ObjTestFlagBit21(s32 arg0);
s32 BtlScene_IsCharInView(s32 arg0);
void func_00128EF0(void);
void func_00128F08(void);
void func_00128F90(s32 arg0);
void func_001995A8(u8 *arg0, s32 arg1, f32 farg0);
extern f32 D_00384D68;
extern s32 gBtlCamView;

void func_0019A340(u8 *arg0) {
    f32 var_f20;
    u8 *temp_s1;

    var_f20 = 1.0f;
    temp_s1 = *(u8 **)(arg0 + 0x38);
    if (BtlCharApi_IsHidden(*(s32 *)(temp_s1 + 0x4C)) != 0) {
        return;
    }
    if ((BtlScene_IsCharInView(*(s32 *)(temp_s1 + 0x4C)) != 0) && (BtlCharApi_ObjTestFlagBit21(*(s32 *)(temp_s1 + 0x4C)) != 0)) {
        var_f20 = D_00384D68;
    }
    func_00128EF0();
    func_00128F90(gBtlCamView + 0x100);
    func_001995A8(temp_s1, *(s32 *)(temp_s1 + 0x4C), var_f20);
    func_00128F08();
}
