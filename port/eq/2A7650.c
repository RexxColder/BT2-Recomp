#include "common.h"

s32 BtlScript_GetText(s32 a0, s32 a1);
s32 Font_GetGlyphHeight(void);
s32 Gsc_GetIntOr(s32 a0);
void func_001017F0(s32 a0, s32 a1, s32 a2);
s32 func_002A0010(s32 a0);
s32 func_002A0EA8(s32 a0);
s32 func_002A3E38(s32 a0, u8 *a1);
void *func_002A3E48(void);
void *func_002A3E80(s32 a0);
void func_002A3EA8(s32 a0, s32 a1);
void func_002A4098(s32 a0);
extern u8 *D_00387F2C;
extern s32 D_003B0C34 __attribute__((section(".data")));
extern s32 D_003B29BC __attribute__((section(".data")));

s32 func_002A7650(s32 arg0, u8 *arg1) {
    s32 var_s4;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s3;
    s32 var_a0;
    s32 temp_v0;
    s32 temp_a2;
    s32 temp_a1;
    s32 temp_h;
    s32 temp_r;
    s32 temp_t;
    f32 temp_x;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v1;

    var_s4 = 0;
    switch (arg0) {
    case 0:
        temp_v0 = func_002A3E38(arg0, arg1);
        *(s32 *)(arg1 + 4) = 0;
        *(s32 *)(arg1 + 0) = temp_v0;
        temp_s0 = func_002A3E48();
        D_003B29BC = *(s32 *)(arg1 + 0);
        *(u8 *)(arg1 + 8) = (u8)(func_002A0010(0x6E) == 0);
        func_002A0010(0x73);
        *(s32 *)(arg1 + 0xC) = Gsc_GetIntOr(0);
        temp_a2 = *(s32 *)(temp_s0 + 8);
        if (temp_a2 >= 0) {
            temp_r = temp_a2;
            if (*(s32 *)(D_00387F2C + 0x1008) & 1) {
                temp_r = temp_a2 + 0x13F6;
            }
            func_001017F0(temp_r, 0, temp_a2);
        }
        var_s1 = *(s32 *)(arg1 + 0xC);
        if (*(s32 *)(arg1 + 0) >= var_s1) {
            var_s3 = 0;
            do {
                func_002A3EA8(var_s1, 0);
                temp_s0_2 = (u8 *)func_002A3E80(var_s1);
                temp_v1 = temp_s0_2 + 0x10;
                temp_a1 = *(s32 *)(temp_v1 + 0x14);
                temp_h = Font_GetGlyphHeight();
                temp_x = (f32)(*(s32 *)(temp_s0_2 + 0x64))
                       + ((f32)var_s3 * ((f32)(temp_h + temp_a1) * (*(f32 *)(temp_v1 + 0x4) * *(f32 *)(temp_v1 + 0x8))));
                /* cvt.w.s: truncates toward zero */
                temp_t = (s32)temp_x;
                *(s32 *)(temp_s0_2 + 0x64) = temp_t;
                var_a0 = var_s1;
                temp_r = BtlScript_GetText(var_a0, temp_a1);
                var_s1 += 1;
                temp_r = func_002A0EA8(temp_r);
                var_s3 = var_s3 + temp_r + 1;
            } while (*(s32 *)(arg1 + 0) >= var_s1);
        }
        return var_s4;
    case 2:
        if (*(s32 *)(arg1 + 4) != 0) {
            var_s4 = 1;
        } else if (D_003B0C34 & 0x4000) {
            *(s32 *)(arg1 + 4) = 1;
        }
        return var_s4;
    case 1:
        if (*(u8 *)(arg1 + 8) != 0) {
            if (*(s32 *)(arg1 + 0) >= 0) {
                var_s1_2 = 0;
                do {
                    func_002A4098(var_s1_2);
                    var_s1_2 += 1;
                } while (*(s32 *)(arg1 + 0) >= var_s1_2);
            }
        }
        return var_s4;
    default:
        return 0;
    }
}
