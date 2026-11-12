#include "common.h"

u8 *func_002768D8(s32 arg0);
void func_0027D7B8(s32 arg0);
void func_0027EC18(u8 *arg0);
void func_0027C320(u8 *arg0, s32 arg1);
void func_002794C0(u8 *arg0);
void func_00280500(void);
void func_00280988(u8 *arg0, s32 arg1);
void func_002820C8(u8 *arg0);
void func_00285D98(u8 *arg0);
void sceVu0InversMatrix(s32 *arg0, s32 arg1);

extern u8 *D_003876A0;
extern u8 *D_00387AFC;
extern s32 gBtlCamView;

void func_00280F18(void) {
    s32 sp[16];
    s64 temp_s0;
    s64 temp_v1_2;
    s64 var_a1;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_v1;

    temp_a0 = D_00387AFC;
    if (*(u8 *)(temp_a0 + 0x3CCA) == 0) {
        if (*(u8 *)(temp_a0 + 0x3CC8) != 0) {
            func_0027D7B8(1);
            *(u8 *)(D_00387AFC + 0x3CC8) = 0;
        }
        if (*(u8 *)(temp_a0 + 0x3CC9) != 0) {
            func_0027D7B8(0);
            *(u8 *)(D_00387AFC + 0x3CC8) = 0;
        }
        func_00285D98(temp_a0);
        var_a1 = *(s64 *)(D_003876A0 + 0x4D8);
        temp_a0_2 = D_00387AFC;
        if (!(var_a1 & 2)) {
            if ((*(u8 *)(temp_a0_2 + 0x3CC1) != 0) && ((var_a1 & 3) != 0)) {
                sceVu0InversMatrix(sp, gBtlCamView);
                if (*(f32 *)(D_00387AFC + 0x3CC4) < *(f32 *)((u8 *)sp + 0x34)) {
                    func_00280988(D_00387AFC + 0x1040, 0);
                } else {
                    func_00280988(D_00387AFC + 0xA80, 0);
                }
            } else {
                func_00280988(temp_a0_2 + 0xA80, (s32)var_a1);
            }
        } else {
            func_00280988(temp_a0_2 + 0xA80, (s32)var_a1);
        }
        temp_v1 = D_003876A0;
        temp_s0 = (s64)0x8000 << 43;
        if (!(*(s64 *)(temp_v1 + 0x4D8) & temp_s0)) {
            func_0027EC18(D_00387AFC + 0x1600);
            if (!(*(s64 *)(D_003876A0 + 0x4D8) & temp_s0)) {
                func_0027C320(D_00387AFC + 0x4C0, 1);
            }
        }
        temp_v1_2 = *(s64 *)(temp_v1 + 0x4D8);
        if ((temp_v1_2 & 3) && !(temp_v1_2 & 2)) {
            func_002794C0(D_00387AFC + 0x3100);
        }
        if ((func_002768D8(9) != NULL) && (*func_002768D8(9) != 0)) {
            func_00280500();
        }
        func_002820C8(D_00387AFC + 0x2F00);
    }
}
