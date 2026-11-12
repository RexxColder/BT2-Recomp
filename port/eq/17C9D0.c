#include "common.h"

extern f32 D_00384A58;
extern s32 gBtlCamView;

s32 BtlCharApi_IsHidden(s32 arg0);
s32 BtlCharApi_ObjTestFlagBit21(s32 arg0);
s32 BtlScene_IsCharInView(s32 arg0);
void func_00128EF0(void);
void func_00128F08(void);
void func_00128F90(s32 arg0);
void func_00179A78(u8 *arg0, s32 arg1, f32 farg0);
void func_0017B8B8(u8 *arg0, s32 arg1, f32 farg0);

void EftAuraTask_Draw(u8 *arg0) {
    f32 f20 = 1.0f;
    u8 *s1 = *(u8 **)(arg0 + 0x38);

    if (BtlCharApi_IsHidden(*(s32 *)(s1 + 0x68)) != 0) {
        return;
    }
    if (*(s32 *)(s1 + 0) & 4) {
        return;
    }
    if (BtlScene_IsCharInView(*(s32 *)(s1 + 0x68)) == 0) {
    } else if (BtlCharApi_ObjTestFlagBit21(*(s32 *)(s1 + 0x68)) != 0) {
        f20 = D_00384A58;
    }
    func_00179A78(s1, *(s32 *)(s1 + 0x68), f20);
    if (*(s32 *)(s1 + 0) & 0x20) {
        return;
    }
    func_00128EF0();
    func_00128F90(gBtlCamView + 0x100);
    func_0017B8B8(s1, *(s32 *)(s1 + 0x68), f20);
    func_00128F08();
}
