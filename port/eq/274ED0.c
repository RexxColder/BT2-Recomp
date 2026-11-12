#include "common.h"

void Vu1Pkt_LoadProg7(u8 *arg0);
void StgModel_SetDrawEnv(void);
void StgModel_SetTexture(s32 arg0, u8 *arg1, s32 arg2);
void Vu1Pkt_CallProg7(f32 farg0, u8 *arg0);
void func_00276040(void);
void func_002760C8(void);
void func_0029D5C8(u8 *arg0, u8 *arg1);
extern u8 *gBtlStage;

s32 func_00274ED0(s32 arg0, u8 *arg1) {
    s32 var_fp;
    s32 var_a2;
    s32 var_s3;
    s32 var_s5;
    s32 temp_s4;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a1;
    u8 *temp_s2;
    u8 *temp_s6;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *var_s0;
    u8 *var_s1;

    var_fp = arg0;
    temp_a0 = *(u8 **)(gBtlStage + 0x5C);
    temp_s6 = temp_a0 + (*(s32 *)(gBtlStage + 0x1C) * 4);
    if (*(u16 *)(temp_s6 + 0x32) != 0) {
        var_s5 = 0;
        Vu1Pkt_LoadProg7(temp_a0);
        var_fp = 0;
        StgModel_SetDrawEnv();
        func_00276040();
        temp_a0_2 = gBtlStage;
        temp_s2 = *(u8 **)(temp_a0_2 + 0x5C) + (*(s32 *)(temp_s6 + 0x34) * 4);
        if (*(u16 *)(temp_s6 + 0x32) != 0) {
            var_a2 = 0;
loop_5:
            temp_v1 = temp_s2 + var_a2;
            temp_s4 = var_a2;
            var_s1 = NULL;
            var_s3 = 0;
            if (*(u16 *)(temp_v1 + 2) != 0) {
                var_s0 = *(u8 **)(temp_a0_2 + 0x5C) + (*(s32 *)(temp_v1 + 4) * 4);
                do {
                    if (*(u8 *)(arg1 + *(u16 *)var_s0) != 0) {
                        temp_a1 = gBtlStage;
                        if (var_s1 == NULL) {
                            StgModel_SetTexture(*(u16 *)(temp_s2 + var_a2), temp_a1, var_a2);
                        }
                        temp_v1_2 = *(u8 **)(temp_a1 + 0x5C);
                        var_s1 = temp_v1_2 + (*(s32 *)(var_s0 + 8) * 4);
                        func_0029D5C8(temp_v1_2 + (*(s32 *)(var_s0 + 0xC) * 4), temp_a1);
                        Vu1Pkt_CallProg7((f32)*(u8 *)(var_s0 + 4), var_s1);
                    }
                    var_a2 = temp_s4;
                    var_s3 += 1;
                    var_s0 += 0x10;
                } while (var_s3 < (s32)*(u16 *)(temp_s2 + var_a2 + 2));
            }
            var_s5 += 1;
            if (var_s5 < (s32)*(u16 *)(temp_s6 + 0x32)) {
                var_a2 = var_s5 * 0x10;
                goto loop_5;
            }
        }
        func_002760C8();
    }
    return var_fp;
}
