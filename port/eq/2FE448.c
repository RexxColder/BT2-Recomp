#include "common.h"

void func_002EFA40(void *arg0, s32 arg1);
void func_002EFAB8(void *arg0, s32 arg1);
void func_002FC550(s32 arg0);
s32 func_002FD318(s32 *arg0, void *arg1);
void func_002FDF58(s8 *arg0, void *arg1);
s32 sceCdSync(s32 arg0);

extern s32 D_00356CF0[] __attribute__((section(".data")));
extern s32 D_00356E18[] __attribute__((section(".data")));
extern s32 D_0037E4C8[] __attribute__((section(".data")));
extern s32 D_0037E4E0[] __attribute__((section(".data")));
extern s32 D_0037E4F8[] __attribute__((section(".data")));
extern s32 D_0037E510[] __attribute__((section(".data")));

s32 func_002FE448(u8 *arg0, s32 arg1) {
    s32 sp[12];
    s32 sp30 = 0;
    s32 var_s4 = 0;
    s32 var_s7 = 0;
    u8 *var_s2;
    s8 *temp_s1;

    if (arg1 > 0) {
        var_s2 = arg0;
        do {
            temp_s1 = (s8 *)(arg0 + ((D_00356CF0[2] * 8) + ((D_00356CF0[3] * var_s4) + var_s4)));
            if (*temp_s1 != 0) {
                func_002FDF58(temp_s1, D_00356E18);
                func_002FC550(0x9400);
                do {
                } while (sceCdSync(1) == 1);
                func_002FC550(0x9401);
                func_002FC550(0x9500);
                if (func_002FD318(sp, D_00356E18) != 1) {
                    sp30 += 1;
                    func_002FC550(0x9502);
                    func_002EFA40(D_0037E4E0, (s32)temp_s1);
                } else {
                    var_s7 += 1;
                    func_002FC550(0x9501);
                    *(s32 *)(var_s2) = sp[0];
                    *(s32 *)(var_s2 + 4) = sp[1];
                    func_002EFA40(D_0037E4C8, (s32)temp_s1);
                }
            }
            var_s4 += 1;
            var_s2 += 8;
        } while (var_s4 < arg1);
    }
    func_002EFA40(D_0037E4F8, var_s7);
    if (sp30 > 0) {
        func_002EFAB8(D_0037E510, 0xA);
    }
    return var_s7;
}
