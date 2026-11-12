#include "common.h"

s32 func_002A0C10(void);
void func_002A1340(void);
void func_002A12B0(s32 arg0);
void func_002A13E8(void);
void func_002A4940(s32 arg0);
void BattleSetup_FinishEx(s32 arg0);
s32 BtlScript_GetText(s32 arg0);
u32 Font_GetHeight(s32 arg0);
void Font_PrintAt(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_003B0F7C[] __attribute__((section(".data")));
extern u8 D_003B1FF0[] __attribute__((section(".data")));
extern u8 D_003B2654[] __attribute__((section(".data")));

void func_002A38C0(void) {
    u8 *var_s1;
    u8 *var_q;
    s32 var_cnt;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_s5;
    s32 var_s6;
    s32 temp_v0;
    u32 temp_v0_2;

    var_s5 = 0;
loop_1:
    if (var_s5 == 0xD) {
        var_s3 = 0;
        var_s6 = func_002A0C10();
        func_002A1340();
        var_s1 = D_003B0F7C;
        do {
            if (*(u8 *)(var_s1 + 0xC) != 0) {
                temp_v0 = *(s8 *)(var_s1 + 3);
                /* TEMP/CANDIDATO: el guion guarda el lado real en +6; +3 trae el byte bajo del text id. */
                if (temp_v0 != 0 && temp_v0 != 1 && temp_v0 != -1) {
                    temp_v0 = *(s8 *)(var_s1 + 6);
                }
                if (temp_v0 == 0) {
                    var_s2 = *(s32 *)(var_s1 + 0x50);
                    var_s0 = *(s32 *)(var_s1 + 0x54);
                } else if (temp_v0 > 0) {
                    if (temp_v0 == 1) {
                        var_s2 = *(s32 *)(var_s1 + 0x58);
                        var_s0 = *(s32 *)(var_s1 + 0x5C);
                    } else {
                        var_s2 = 0;
                        var_s0 = 0;
                    }
                } else if (temp_v0 == -1) {
                    var_s2 = *(s32 *)(var_s1 + 0x60);
                    var_s0 = *(s32 *)(var_s1 + 0x64);
                } else {
                    var_s2 = 0;
                    var_s0 = 0;
                }
                if ((*(s32 *)(D_003B2654 + 4) == 0x15B) && (var_s3 == 0)) {
                    *(s32 *)(var_s1 + 0x20) = 1;
                }
                func_002A12B0((s32)(var_s1 + 0x10));
                temp_v0_2 = Font_GetHeight(BtlScript_GetText(*(s8 *)(var_s1 + 1)));
                var_s0 -= (s32)((temp_v0_2 >> 0x1F) + temp_v0_2) >> 1;
                Font_PrintAt(var_s2, var_s0, BtlScript_GetText(*(s8 *)(var_s1 + 1)));
            }
            var_s3 += 1;
            var_s1 += 0x68;
        } while (var_s3 < 0x20);
        func_002A13E8();
        BattleSetup_FinishEx(var_s6);
    }
    var_cnt = 0x21;
    var_q = D_003B1FF0;
    do {
        if ((*(s8 *)(var_q + 0x18) != 0) && (*(s8 *)(var_q + 0x19) == var_s5)) {
            func_002A4940((s32)var_q);
        }
        var_cnt -= 1;
        var_q += 0x28;
    } while (var_cnt >= 0);
    var_s5 += 1;
    if (var_s5 < 0x10) {
        goto loop_1;
    }
}
