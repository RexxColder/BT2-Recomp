#include "common.h"

s32 func_00276D00(s32 arg0, s32 arg1, s32 arg2);
void StgModel_SetDrawEnv(void);
void StgModel_SetTexture(s32 arg0);
void Vu1Pkt_CallProg5(s32 arg0, s32 arg1);
void func_0029E938(s32 arg0);
s32 sceVu0UnitMatrix(s32 arg0);
void Dma_AddZbuf(s32 arg0, s32 arg1);
void func_00130E30(void);

extern u8 *gBtlStage;
extern u8 *D_003876A0;

void func_00275B38(u8 *arg0) {
    s32 sp[16];
    s32 sp40;
    s32 stage_rec;
    s32 temp_a0;
    s32 s5;
    s32 s1;
    s32 s0;
    s32 fp;
    s32 s2;
    s32 s3;

    sp40 = *(s32 *)(gBtlStage + 0x5C) + *(s32 *)(gBtlStage + 0x2C) * 4;
    temp_a0 = *(s32 *)(gBtlStage + 0x1C) * 4;
    stage_rec = *(s32 *)(gBtlStage + 0x5C) + temp_a0;

    if ((*(s32 *)(D_003876A0 + 0x4D8) & 0x2000) != 0) {
        return;
    }
    if ((*(s32 *)(gBtlStage + 0x8) & 1) != 0) {
        return;
    }
    if (func_00276D00(temp_a0, 0, (s32)gBtlStage) == 0) {
        return;
    }
    StgModel_SetDrawEnv();

    if (*(u16 *)(stage_rec + 2) != 0) {
        sceVu0UnitMatrix((s32)sp);
        func_0029E938((s32)(arg0 + 0xC0));
        s5 = *(s32 *)(gBtlStage + 0x5C) + *(s32 *)(stage_rec + 4) * 4;
        Dma_AddZbuf(0xE0, 1);
        if (*(u16 *)(stage_rec + 2) != 0) {
            s1 = s5;
            fp = 0;
            do {
                s2 = 0;
                s3 = 0;
                if (*(u16 *)(s1 + 2) != 0) {
                    s0 = *(s32 *)(gBtlStage + 0x5C) + *(s32 *)(s1 + 4) * 4;
                    do {
                        if (*(u8 *)(sp40 + *(u16 *)(s0 + 0)) != 0) {
                            if (s2 == 0) {
                                StgModel_SetTexture(*(u16 *)(s1 + 0));
                            }
                            s2 = *(s32 *)(gBtlStage + 0x5C) + *(s32 *)(s0 + 8) * 4;
                            Vu1Pkt_CallProg5(s2, (s32)sp);
                        }
                        s3 += 1;
                        s0 += 0x10;
                    } while (s3 < *(u16 *)(s1 + 2));
                }
                fp += 1;
                s1 += 0x10;
            } while (fp < *(u16 *)(stage_rec + 2));
        }
        Dma_AddZbuf(0xE0, 0);
    }
    Dma_AddZbuf(0xE0, 1);
    func_00130E30();
    Dma_AddZbuf(0xE0, 0);
}
