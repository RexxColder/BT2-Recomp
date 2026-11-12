#include "common.h"

extern u8 D_00387DF0;
extern u8 D_00387DF1;
extern s32 D_00387EDC;
extern s32 D_00387EE8;
extern s32 D_00387EF4;

s32 Dma_BeginDirect(void);
void Dma_EndDirect();
void Font_Home(void);
void func_002A16F8(s32 arg0, s32 arg1);
void func_002A21A0(s32 arg0);
void Tex_Upload(s32 arg0, s32 arg1, s32 arg2);

void BattleSetup_FinishEx(s32 arg0) {
    u8 *ent;
    u8 *rec;
    u8 *cur;
    u8 *hdr;
    s32 s2;
    s32 k;
    s32 p;
    s32 cb;
    s32 cnt;

    if (D_00387DF0 == 0) {
        return;
    }
    if (D_00387DF1 == 0) {
        return;
    }
    if (!(arg0 < D_00387EF4)) {
        return;
    }

    ent = (u8 *)D_00387EDC;
    for (k = 7; k >= 0; k--, ent += 0x14) {
        p = *(s32 *)ent;
        if (p != 0) {
            Tex_Upload(*(s32 *)((u8 *)p + 8), *(s32 *)(ent + 4), *(s32 *)(ent + 8));
        }
    }

    s2 = 0x3A40;
    for (k = arg0, rec = (u8 *)D_00387EE8 + 0x4C * arg0; k < D_00387EF4; k++, rec += 0x4C) {
        cb = *(s32 *)(rec + 0x40);
        if (cb != 0) {
            *(s32 *)(rec + 0x48) = s2;
            s2 += ((s32 (*)(s32))cb)(s2);
        }
    }

    cur = (u8 *)Dma_BeginDirect();
    ((u64 *)cur)[0] = 0x1000000000008008ULL;
    ((u64 *)cur)[1] = 0xE;
    ((u64 *)cur)[2] = 0;
    ((u64 *)cur)[3] = 8;
    ((u64 *)cur)[4] = 1;
    ((u64 *)cur)[5] = 0x46;
    ((u64 *)cur)[6] = 0x60;
    ((u64 *)cur)[7] = 0x14;
    ((u64 *)cur)[8] = 0;
    ((u64 *)cur)[9] = 0x47;
    ((u64 *)cur)[10] = 0x0000008000008080ULL;
    ((u64 *)cur)[11] = 0x3B;
    ((u64 *)cur)[12] = 0x44;
    ((u64 *)cur)[13] = 0x42;
    ((u64 *)cur)[14] = 0x1310000E0ULL;
    ((u64 *)cur)[15] = 0x4E;
    ((u64 *)cur)[16] = 0x156;
    ((u64 *)cur)[17] = 0;
    cur += 0x90;

    if (arg0 < D_00387EF4) {
        rec = (u8 *)D_00387EE8 + 0x4C * arg0;
        k = arg0;
        s2 = 6;
        do {
            ((u64 *)cur)[0] = 0x1000000000008001ULL;
            ((u64 *)cur)[1] = 0xE;
            cur += 0x10;
            ((u64 *)cur)[0] = ((u64)*(u16 *)(rec + 0x32) << 48) | ((u64)*(u16 *)(rec + 0x2E) << 32) |
                              ((u64)*(u16 *)(rec + 0x30) << 16) | (u64)*(u16 *)(rec + 0x2C);
            ((u64 *)cur)[1] = 0x40;
            cur += 0x10;
            hdr = cur;
            ((u64 *)hdr)[0] = 0x6400000000008000ULL;
            ((u64 *)hdr)[1] = 0x535316;
            cur += 0x10;
            func_002A16F8((s32)&cur, (s32)rec);
            cnt = ((s32)(cur - hdr) >> 3) - 2;
            *(u16 *)hdr = (u16)(cnt / 6);
            rec += 0x4C;
            k++;
        } while (k < D_00387EF4);
    }

    ((u64 *)cur)[0] = 0x1000000000008002ULL;
    ((u64 *)cur)[1] = 0xE;
    cur += 0x10;
    ((u64 *)cur)[0] = 0x310000E0ULL;
    ((u64 *)cur)[1] = 0x4E;
    cur += 0x10;
    ((u64 *)cur)[0] = 0x1BF000001FF0000ULL;
    ((u64 *)cur)[1] = 0x40;
    cur += 0x10;
    Dma_EndDirect((s32)cur, 0x310000E0, 0x4E, 0x1BF000001FF0000ULL, 0x40);
    Font_Home();
    func_002A21A0(arg0);
}
