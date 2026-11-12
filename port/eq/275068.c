#include "common.h"

extern u8 *D_003876A0;
extern u8 *gBtlStage;

extern s32 StgModel_SetDrawEnv();
extern s32 StgModel_SetBlendEnv();
extern s32 StgModel_SetTexture();
extern s32 func_00276D00();
extern s32 func_00276AC8();
extern s32 Vu1Pkt_LoadProg4();
extern s32 Vu1Pkt_CallProg4();
extern s32 Dma_AddZbuf();
extern s32 func_00130E30();
extern s32 func_00271A00();
extern s32 func_00136FF8();
extern s32 func_00275FB8();
extern s32 func_002729D0();
extern s32 func_00274ED0();

/* draws one list of cnt records (16 bytes each) at rec */
static void drawList(u8 *rec, s32 cnt, u8 *mask)
{
    s32 i, j;
    for (i = 0; i < cnt; i++) {
        u8 *s2 = rec + i * 16;
        u8 *s0;
        u8 *s1 = 0;
        if (*(u16 *)(s2 + 2) == 0) continue;
        s0 = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s2 + 4) * 4;
        for (j = 0; j < *(u16 *)(s2 + 2); j++, s0 += 16) {
            if (mask[*(u16 *)s0] == 0) continue;
            if (s1 == 0) StgModel_SetTexture(*(u16 *)s2);
            s1 = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s0 + 8) * 4;
            Vu1Pkt_CallProg4(s1);
        }
    }
}

s32 func_00275068(u8 *a0)
{
    s32 sp8 = -1;
    s32 spC = 0;
    u8 *stg, *base, *s6, *mask, *s4, *s5;
    s32 v, i, j, a3;

    if (*(u64 *)(D_003876A0 + 0x4D8) & 0x2000) return (s32)(*(u64 *)(D_003876A0 + 0x4D8) & 0x2000);
    stg = gBtlStage;
    if (*(s32 *)(stg + 8) & 1) return *(s32 *)(stg + 0x2C);
    base = *(u8 **)(stg + 0x5C);
    s6 = base + *(s32 *)(stg + 0x1C) * 4;
    mask = base + *(s32 *)(stg + 0x2C) * 4;
    StgModel_SetDrawEnv();
    if (func_00276D00()) {
        v = *(u16 *)(s6 + 0xA);
    } else {
        if (*(u16 *)(s6 + 2)) {
            sp8 = 0;
            Vu1Pkt_LoadProg4(a0 + 0xC0);
            s4 = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s6 + 4) * 4;
            Dma_AddZbuf(0xE0, 1);
            drawList(s4, *(u16 *)(s6 + 2), mask);
            Dma_AddZbuf(0xE0, 0);
        }
        if (!(*(u64 *)(D_003876A0 + 0x4D8) & 4)) {
            Dma_AddZbuf(0xE0, 1);
            func_00130E30(0xE0);
            Dma_AddZbuf(0xE0, 0);
        }
        v = *(u16 *)(s6 + 0xA);
    }
    if (v) {
        if (sp8) {
            sp8 = 0;
            Vu1Pkt_LoadProg4(a0 + 0xC0);
        }
        s4 = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s6 + 0xC) * 4;
        Dma_AddZbuf(0xE0, 0);
        drawList(s4, *(u16 *)(s6 + 0xA), mask);
    }
    if (func_00276D00() == 1 && *(u16 *)(s6 + 0x1A)) {
        spC = 1;
        Vu1Pkt_LoadProg4(a0 + 0xC0);
        Dma_AddZbuf(0xE0, 1);
        func_00271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0x3F80000000000000LL);
        s4 = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s6 + 0x1C) * 4;
        StgModel_SetBlendEnv();
        Dma_AddZbuf(0xE0, 1);
        drawList(s4, *(u16 *)(s6 + 0x1A), mask);
        Dma_AddZbuf(0xE0, 0);
    }
    if (func_00276D00() == 1) func_00136FF8();
    func_00275FB8();
    if (*(u16 *)(s6 + 0x12)) {
        s5 = a0 + 0xC0;
        Vu1Pkt_LoadProg4(s5);
        s4 = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s6 + 0x14) * 4;
        for (i = 0; i < *(u16 *)(s6 + 0x12); i++) {
            u8 *rec = s4 + i * 16;
            u8 *s0;
            u8 *s1 = 0;
            u8 *sb = *(u8 **)(gBtlStage + 0x5C);
            if (*(u16 *)(rec + 2) == 0) continue;
            s0 = sb + *(s32 *)(rec + 4) * 4;
            for (j = 0; j < *(u16 *)(rec + 2); j++, s0 += 16) {
                if (mask[*(u16 *)s0] == 0) continue;
                if (s1 == 0) {
                    s32 off = *(s32 *)(rec + 8);
                    if (off == 0) {
                        StgModel_SetTexture(*(u16 *)rec);
                    } else {
                        u8 *a = *(u8 **)(gBtlStage + 0x5C) + off * 4;
                        u32 hdr = *(u16 *)a;
                        if ((hdr & 4) && !(*(u64 *)(D_003876A0 + 0x4D8) & 0x100)) {
                            s32 cnt = *(u16 *)(a + 2);
                            u8 *t1 = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(a + 4) * 4;
                            u8 *a1 = t1;
                            s32 t2 = 0;
                            s32 t4 = hdr & 1;
                            if (0 < cnt) {
                                for (;;) {
                                    u32 a0v = *(u16 *)(rec + 0xC);
                                    if (*(u32 *)a1 == (a0v & 0xFFFF7FFF)) {
                                        if (t4) {
                                            if (t2 == cnt - 1) *(u16 *)(rec + 0xC) = *(u16 *)t1;
                                            else *(u16 *)(rec + 0xC) = *(u16 *)(a1 + 4);
                                        } else if (a0v & 0x8000) {
                                            if (t2 == 0) *(u16 *)(rec + 0xC) = *(u16 *)(t1 + 4);
                                            else *(u16 *)(rec + 0xC) = *(u16 *)(a1 - 4) | 0x8000;
                                        } else if (t2 == cnt - 1) {
                                            *(u16 *)(rec + 0xC) = *(u16 *)(t1 + cnt * 4 - 8) | 0x8000;
                                        } else {
                                            *(u16 *)(rec + 0xC) = *(u16 *)(a1 + 4);
                                        }
                                        break;
                                    }
                                    t2++;
                                    a1 += 4;
                                    if (!(t2 < cnt)) break;
                                }
                            }
                        }
                        StgModel_SetTexture(*(u8 *)(rec + 0xC));
                    }
                }
                {
                    u8 *sb2 = *(u8 **)(gBtlStage + 0x5C);
                    s32 pv = *(u8 *)(s0 + 3);
                    s1 = sb2 + *(s32 *)(s0 + 8) * 4;
                    if (pv != sp8) {
                        if (pv == 0) Vu1Pkt_LoadProg4(s5);
                        sp8 = *(u8 *)(s0 + 3);
                        pv = *(u8 *)(s0 + 3);
                    }
                    if (pv == 0) Vu1Pkt_CallProg4(s1);
                }
            }
        }
    }
    func_002729D0();
    if (func_00276AC8() == 8) spC = func_00274ED0(spC, mask);
    if (func_00276D00() == 0 && func_00276AC8() != 5) {
        if (*(u16 *)(s6 + 0x1A)) {
            spC = 1;
            Vu1Pkt_LoadProg4(a0 + 0xC0);
            Dma_AddZbuf(0xE0, 1);
            func_00271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0x3F80000000000000LL);
            s4 = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s6 + 0x1C) * 4;
            StgModel_SetBlendEnv();
            Dma_AddZbuf(0xE0, 0);
            drawList(s4, *(u16 *)(s6 + 0x1A), mask);
            Dma_AddZbuf(0xE0, 0);
        }
    }
    if (*(u16 *)(s6 + 0x22)) {
        spC = 1;
        Vu1Pkt_LoadProg4(a0 + 0xC0);
        Dma_AddZbuf(0xE0, 1);
        func_00271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0x3F80000000000000LL);
        s4 = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s6 + 0x24) * 4;
        Dma_AddZbuf(0xE0, 1);
        StgModel_SetBlendEnv();
        drawList(s4, *(u16 *)(s6 + 0x22), mask);
        Dma_AddZbuf(0xE0, 0);
    }
    if (*(u16 *)(s6 + 0x2A)) {
        spC = 1;
        Vu1Pkt_LoadProg4(a0 + 0xC0);
        Dma_AddZbuf(0xE0, 1);
        func_00271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0x3F80000000000000LL);
        s4 = *(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s6 + 0x2C) * 4;
        StgModel_SetBlendEnv();
        drawList(s4, *(u16 *)(s6 + 0x2A), mask);
        Dma_AddZbuf(0xE0, 0);
    }
    if (func_00276AC8() != 8) spC = func_00274ED0(spC, mask);
    Dma_AddZbuf(0xE0, 0);
    if (spC == 0) return StgModel_SetDrawEnv();
    return spC;
}
